#include "Processes.h"

size_t get_breads_tbd(const Args* args) {
    return (args->breads > args->mixer_capacity) ? args->mixer_capacity : args->breads;
}

size_t get_facility_idx_or_first(const std::vector<Facility>& facilities) {
    uint64_t idx = 0;
    for (const auto& facility : facilities) {
        if (!facility.Busy()) {
            return idx;
        }
        idx++;
    }
    return (idx < facilities.size()) ? idx : 0;
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

    //    std::stringstream msg;
    //    msg << "Total bake time: "
    //        << (program->stats->mix_duration->MeanValue() + program->stats->cut_duration->MeanValue() +
    //            program->stats->fermentation_duration->MeanValue() + program->stats->bake_duration->MeanValue() +
    //            program->stats->load_duration->MeanValue()) /
    //               SECONDS_PER_MINUTE
    //        << " minutes\n";
    //    Print(msg.str().c_str());
}

void OrderProcess::Behavior() {
    auto& sources = program->sources;
    auto args = program->args;

    // Start Day Order
    Enter(*sources->orders, sources->orders->Capacity());

    //
    while (args->breads > 0) {
        DEBUG_PRINT("OrderProcess breads_tbd: %zu\n", get_breads_tbd(program->args));

        // Start mixing
        (new MixProcess(this->program, get_breads_tbd(args)))->Activate();

        //
        args->breads -= get_breads_tbd(args);
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
MixProcess::MixProcess(Program* _program, const size_t _breads_tbd) : breads_tbd(_breads_tbd), program(_program) {}

MixProcess::~MixProcess() = default;

void MixProcess::Behavior() {
    auto idx = get_facility_idx_or_first(program->sources->mixers);
    Seize(program->sources->mixers[idx]);

    DEBUG_PRINT("MixProcess breads_tbd: %d\n", breads_tbd);

    //
    const double duration =
        Normal(mix_mean_duration_per_bread_sec * breads_tbd, mix_deviation_duration_per_bread_sec * breads_tbd);
    (*program->stats->mix_duration)(duration);
    Wait(duration);

    // Continue mixers
    Release(program->sources->mixers[idx]);

    // Start Cutting after dough is mixed
    (new CutProcess(program, breads_tbd))->Activate();
}

/******************************************************************************
 * CutProcess
 *****************************************************************************/
CutProcess::CutProcess(Program* _program, const size_t _breads_tbd)
    : breads_tbd(_breads_tbd), program(_program) {}  // Bread_tbd are divided by cart capacity

CutProcess::~CutProcess() = default;

void CutProcess::Behavior() {
    DEBUG_PRINT("CutProcess breads_tbd: %zu\n", breads_tbd);
    auto idx = get_facility_idx_or_first(program->sources->tables);

    //
    Seize(program->sources->tables[idx]);

    // TODO: Better handle the case when cart if full go to fermenting (Now two carts are used)
    const double duration =
        Normal(cut_mean_duration_per_bread_sec * breads_tbd, cut_deviation_duration_per_bread_sec * breads_tbd);
    (*program->stats->cut_duration)(duration);
    Wait(duration);

    //
    Release(program->sources->tables[idx]);

    // Start Fermentation after all mixed dough is cut
    (new FermentationProcess(program, breads_tbd / program->args->cart_capacity))->Activate();
}

/******************************************************************************
 * FermentationProcess
 *****************************************************************************/
FermentationProcess::FermentationProcess(Program* _program, const size_t _breads_tbd)
    : program(_program), breads_tbd(_breads_tbd) {}

FermentationProcess::~FermentationProcess() = default;

void FermentationProcess::Behavior() {
    const size_t carts_tbd = breads_tbd / program->args->cart_capacity;
    DEBUG_PRINT("FermentationProcess carts/Capacity: %zu/%zu\n", carts_tbd, program->sources->fermenting->Capacity());

    //
    Enter(*program->sources->fermenting, carts_tbd);

    // Fermentation bunch of breads
    const double duration =
        Normal(fermentation_mean_duration_per_bread_sec, fermentation_deviation_duration_per_bread_sec);
    (*program->stats->fermentation_duration)(duration);
    Wait(duration);

    //
    Leave(*program->sources->fermenting, carts_tbd);

    //     Start Baking after one heap of mixed dough is fermented
    (new BakeProcess(this->program, breads_tbd))->Activate();
}

/******************************************************************************
 * BakeProcess
 *****************************************************************************/
BakeProcess::BakeProcess(Program* _program, const size_t _breads_tbd) : program(_program), breads_tbd(_breads_tbd) {}

BakeProcess::~BakeProcess() = default;

void BakeProcess::Behavior() {
    DEBUG_PRINT("BakeProcess breads_tbd: %zu\n", breads_tbd);
    auto idx = get_facility_idx_or_first(program->sources->tables);

    //
    Seize(program->sources->ovens[idx]);

    //
    double duration = Normal(bake_duration_mean_per_break_sec, bake_duration_deviation_per_bread_sec);
    (*program->stats->bake_duration)(duration);
    Wait(duration);

    //
    Release(program->sources->ovens[idx]);

    // Start Loading after one heap of mixed dough is baked
    //    Enter(*program->sources->loading, 1);
    //    (new LoadProcess(this->program, breads_tbd))->Activate();

    // Leave the bakery after all breads are loaded
    if (breads_tbd < program->args->mixer_capacity) {
        DEBUG_PRINT("Leave Mix%s\n", "");
        Leave(*(program->sources->orders), 1);
    }
}

#if 0
/******************************************************************************
 * LoadProcess
 *****************************************************************************/
LoadProcess::LoadProcess(Program* _program, const int _breads_tbd) : breads_tbd(_breads_tbd), program(_program) {}

LoadProcess::~LoadProcess() = default;

void LoadProcess::Behavior() {
    DEBUG_PRINT("LoadProcess breads_tbd: %d\n", breads_tbd);
    //
    const double duration =
        Normal(load_mean_duration_per_bread_sec * breads_tbd, load_deviation_duration_per_bread_sec * breads_tbd);
    (*program->stats->load_duration)(duration);
    Wait(duration);

    //
    Leave(*program->sources->loading, 1);

    // TODO: Order DONE
}

#endif
