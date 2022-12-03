#include "Processes.h"

size_t get_breads_tbd(const Args* args) {
    return (args->breads > args->mixer_capacity) ? args->mixer_capacity : args->breads;
}

/******************************************************************************
 * OrderProcess
 *****************************************************************************/
OrderProcess::OrderProcess(Program* _program) : program(_program) {}

OrderProcess::~OrderProcess() {
    program->stats->mix_duration->Output();
    program->stats->cut_duration->Output();
    program->stats->fermentation_duration->Output();
    program->stats->bake_duration->Output();
    program->stats->load_duration->Output();

    std::stringstream msg;
    msg << "Total bake time: "
        << (program->stats->mix_duration->MeanValue() + program->stats->cut_duration->MeanValue() +
            program->stats->fermentation_duration->MeanValue() + program->stats->bake_duration->MeanValue() +
            program->stats->load_duration->MeanValue()) /
               SECONDS_PER_MINUTE
        << " minutes\n";
    Print(msg.str().c_str());
}

void OrderProcess::Behavior() {
    auto& sources = program->sources;
    auto args = program->args;

    // Start Day Order
    Enter(*sources->orders, sources->orders->Capacity());

    //
    while (args->breads > 0) {
        // Start mixing
        (new MixProcess(this->program, get_breads_tbd(args)))->Activate();

        // Update breads to be done
        args->breads -= get_breads_tbd(args);

        //
        DEBUG_PRINT("OrderProcess breads_tbd: %zu | Left: %zu\n", get_breads_tbd(program->args), args->breads);
    }

    // Wait for all processes to finish
    DEBUG_PRINT("Wait 1%s\n", "");
    Enter(*sources->orders, sources->orders->Capacity());
    DEBUG_PRINT("Wait 2%s\n", "");
    Leave(*sources->orders, sources->orders->Capacity());
    DEBUG_PRINT("Wait 3%s\n", "");
}

/******************************************************************************
 * MixProcess
 *****************************************************************************/
MixProcess::MixProcess(Program* _program, const size_t _breads_tbd) : program(_program), breads_tbd(_breads_tbd) {}

MixProcess::~MixProcess() = default;

void MixProcess::Behavior() {
    // Init
    Facility* facility = program->sources->get_facility_to_use(program->sources->mixers);
    const double duration = Normal(mix_mean_duration_per_bread_sec * (double)breads_tbd,
                                   mix_deviation_duration_per_bread_sec * (double)breads_tbd);

    //
    DEBUG_PRINT("MixProcess breads_tbd: %zu | Free mixers: %zu | Wait: %f\n", breads_tbd,
                program->sources->get_free_facility_len(program->sources->mixers), duration);

    // Wait
    Seize(*facility);
    (*program->stats->mix_duration)(duration);
    Wait(duration);
    Release(*facility);

    // Continue making loaves
    (new CutProcess(program, breads_tbd))->Activate();
}

/******************************************************************************
 * CutProcess
 *****************************************************************************/
CutProcess::CutProcess(Program* _program, const size_t _breads_tbd)
    : breads_tbd(_breads_tbd), program(_program) {}  // Bread_tbd are divided by cart capacity

CutProcess::~CutProcess() = default;

void CutProcess::Behavior() {
    // Init
    auto facility = program->sources->get_facility_to_use(program->sources->tables);
    const double duration = Normal(cut_mean_duration_per_bread_sec * (double)breads_tbd,
                                   cut_deviation_duration_per_bread_sec * (double)breads_tbd);

    //
    DEBUG_PRINT("CutProcess breads_tbd: %zu | Free tables: %zu | Wait: %f\n", breads_tbd,
                program->sources->get_free_facility_len(program->sources->tables), duration);

    // Wait
    Seize(*facility);
    (*program->stats->cut_duration)(duration);
    Wait(duration);
    Release(*facility);

    // Continue fermentation
    (new FermentationProcess(program, breads_tbd))->Activate();
}

/******************************************************************************
 * FermentationProcess
 *****************************************************************************/
FermentationProcess::FermentationProcess(Program* _program, const size_t _breads_tbd)
    : program(_program), breads_tbd(_breads_tbd) {}

FermentationProcess::~FermentationProcess() = default;

void FermentationProcess::Behavior() {
    // Init
    const size_t carts_tbd = ceil((double)breads_tbd / (double)program->args->cart_capacity);
    const double duration =
        Normal(fermentation_mean_duration_per_bread_sec, fermentation_deviation_duration_per_bread_sec);

    //
    DEBUG_PRINT("FermentationProcess breads_tbd: %zu | Carts: %zu | Wait: %f\n", breads_tbd, carts_tbd, duration);

    // Wait
    Enter(*program->sources->fermenting, carts_tbd);
    (*program->stats->fermentation_duration)(duration);
    Wait(duration);
    Leave(*program->sources->fermenting, carts_tbd);

    // Continue baking
    (new BakeProcess(this->program, breads_tbd))->Activate();
}

/******************************************************************************
 * BakeProcess
 *****************************************************************************/
BakeProcess::BakeProcess(Program* _program, const size_t _breads_tbd) : program(_program), breads_tbd(_breads_tbd) {}

BakeProcess::~BakeProcess() = default;

void BakeProcess::Behavior() {
    // Init
    const size_t carts_tbd = ceil((double)breads_tbd / (double)program->args->cart_capacity);
    const double duration = Normal(bake_duration_mean_per_break_sec, bake_duration_deviation_per_bread_sec);
    const auto facility = program->sources->get_facility_to_use(program->sources->ovens);

    //
    DEBUG_PRINT("BakeProcess breads_tbd: %zu | Ovens: %zu | Wait: %f\n", breads_tbd, program->args->ovens, duration);

    // Wait
    for (size_t i = 0; i < carts_tbd; ++i) {
        Seize(*facility);
        (*program->stats->bake_duration)(duration);
        Wait(duration);
        Release(*facility);
    }

    // Continue loading
    (new LoadProcess(this->program, breads_tbd))->Activate();
}

/******************************************************************************
 * LoadProcess
 *****************************************************************************/
LoadProcess::LoadProcess(Program* _program, const size_t _breads_tbd) : program(_program), breads_tbd(_breads_tbd) {}

LoadProcess::~LoadProcess() = default;

void LoadProcess::Behavior() {
    // Init
    const double duration = Normal(load_mean_duration_per_bread_sec * (double)breads_tbd,
                                   load_deviation_duration_per_bread_sec * (double)breads_tbd);

    //
    DEBUG_PRINT("LoadProcess breads_tbd: %zu | Load Capacity: %zu | Wait: %f\n", breads_tbd,
                program->sources->loading->Capacity(), duration);

    // Wait
    Enter(*program->sources->loading, 1);
    (*program->stats->load_duration)(duration);
    Wait(duration);
    Leave(*program->sources->loading, 1);

    // Leave the bakery
    if (breads_tbd < program->args->mixer_capacity) {
        DEBUG_PRINT("Leave Mix%s\n", "");
        Leave(*(program->sources->orders), 1);
    }
}
