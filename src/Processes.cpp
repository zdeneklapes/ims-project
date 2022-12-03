#include "Processes.h"

/******************************************************************************
 * TODO
 *****************************************************************************/
// TODO: 10361 ERROR
// TODO: Total bake time is not updated after compilation

size_t get_carts_tbd(const size_t breads_tbd, const size_t cart_capacity) {
    return ceil((double)breads_tbd / (double)cart_capacity);
}

/******************************************************************************
 * OrderProcess
 *****************************************************************************/
OrderProcess::OrderProcess(Program* _program) : program(_program) {}

OrderProcess::~OrderProcess() = default;

void OrderProcess::Behavior() {
    // Init
    program->simulation_time = Time;
    auto& sources = program->sources;
    auto args = program->args;

    // Start Day Order
    Enter(*sources->orders, sources->orders->Capacity());

    //
    auto breads_tbd = args->breads;
    while (breads_tbd > 0) {
        (new MixProcess(this->program, Args::get_breads_tbd(breads_tbd, args->mixer_capacity)))->Activate();
        breads_tbd -= Args::get_breads_tbd(breads_tbd, args->mixer_capacity);
        DEBUG_PRINT("OrderProcess breads_tbd: %zu | Left: %zu\n",
                    Args::get_breads_tbd(breads_tbd, args->mixer_capacity), breads_tbd);
    }

    // Wait for all processes to finish
    DEBUG_PRINT("Wait 1%s\n", "");
    Enter(*sources->orders, sources->orders->Capacity());
    DEBUG_PRINT("Wait 2%s\n", "");
    Leave(*sources->orders, sources->orders->Capacity());
    DEBUG_PRINT("Wait 3%s\n", "");

    //
    program->simulation_time = Time - program->simulation_time;
    //    program->print_data();
    program->reinit();
}

/******************************************************************************
 * MixProcess
 *****************************************************************************/
MixProcess::MixProcess(Program* _program, const size_t _breads_tbd) : program(_program), breads_tbd(_breads_tbd) {}

MixProcess::~MixProcess() = default;

void MixProcess::Behavior() {
    // Init
    Facility* facility = program->sources->get_facility_to_use(program->sources->mixers);
    const double duration = Normal(mix_mi_duration_per_bread_sec * (double)breads_tbd,
                                   mix_sigma_duration_per_bread_sec * (double)breads_tbd);

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
    const auto carts_tbd = get_carts_tbd(breads_tbd, program->args->cart_capacity);
    auto facility = program->sources->get_facility_to_use(program->sources->tables);
    const auto mi = cut_mi_duration_per_bread_sec * (double)breads_tbd;
    const auto sigma = cut_sigma_duration_per_bread_sec * (double)breads_tbd;
    const double duration = Normal(mi, sigma);

    //
    DEBUG_PRINT(
        "CutProcess: breads_tbd: %zu | Wait: %f (mi: %f | sigma: %f) | Carts: %zu | Facility: %p | Capacity %zu\n",
        breads_tbd, duration, mi, sigma, carts_tbd, (void*)facility, program->sources->ovens.size());

    // Wait
    Seize(*facility);
    (*program->stats->cut_duration)(duration);
    Wait(duration);
    Release(*facility);

    // Continue By Cart
    for (size_t i = 0; i < carts_tbd; ++i) {
        (new FermentationProcess(program, program->args->cart_capacity))->Activate();
    }
}

/******************************************************************************
 * FermentationProcess
 *****************************************************************************/
FermentationProcess::FermentationProcess(Program* _program, const size_t _breads_tbd)
    : program(_program), breads_tbd(_breads_tbd) {}

FermentationProcess::~FermentationProcess() = default;

void FermentationProcess::Behavior() {
    // Init
    const size_t carts_tbd = get_carts_tbd(breads_tbd, program->args->cart_capacity);
    const double duration = Normal(fermentation_mi_duration_per_bread_sec, fermentation_sigma_duration_per_bread_sec);

    //
    DEBUG_PRINT("FermentationProcess: breads_tbd: %zu | Wait: %f (mi: %f | sigma: %f) | Carts: %zu | Store: %zu/%zu\n",
                breads_tbd, duration, fermentation_mi_duration_per_bread_sec, fermentation_sigma_duration_per_bread_sec,
                carts_tbd, program->sources->fermenting->Used(), program->sources->fermenting->Capacity());

    // Wait
    Enter(*program->sources->fermenting, 1);
    (*program->stats->fermentation_duration)(duration);
    Wait(duration);
    Leave(*program->sources->fermenting, 1);

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
    auto mi = bake_mi_duration_per_break_sec;
    auto sigma = bake_sigma_duration_per_bread_sec;
    const double duration = Normal(mi, sigma);
    Facility* facility = program->sources->get_facility_to_use(program->sources->ovens);

    //
    DEBUG_PRINT(
        "BakeProcess breads_tbd: %zu | Wait: %f (mi: %f | sigma: %f) | Carts: %zu | Facility: %p | Capacity %zu\n",
        breads_tbd, duration, mi, sigma, carts_tbd, (void*)facility, program->sources->ovens.size());

    //
    Seize(*facility);
    (*program->stats->bake_duration)(duration);
    Wait(duration);
    Release(*facility);

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
    auto mi = load_mi_duration_per_bread_sec * (double)breads_tbd;
    auto sigma = load_sigma_duration_per_bread_sec * (double)breads_tbd;
    const double duration = Normal(mi, sigma);

    //
    DEBUG_PRINT("LoadProcess: breads_tbd: %zu | Wait: %f (mi: %f | sigma: %f) | Store: %zu/%zu\n", breads_tbd, duration,
                mi, sigma, program->sources->loading->Used(), program->sources->loading->Capacity());

    // Wait
    Enter(*program->sources->loading, 1);
    (*program->stats->load_duration)(duration);
    Wait(duration);
    Leave(*program->sources->loading, 1);

    // END: Leave the bakery
    if (program->sources->all_sources_free()) {
        DEBUG_PRINT("End%s\n", "");
        Leave(*program->sources->orders, 1);
    } else {
        DEBUG_PRINT("Continue%s\n", "");
    }
}
