#include "Processes.h"

int get_breads_tbd(const Args* args) {
    return args->breads > args->mixer_capacity ? args->mixer_capacity : args->breads;
}

/******************************************************************************
 * WorkShiftProcess
 *****************************************************************************/
WorkShiftProcess::WorkShiftProcess(Program* _program) : program(_program) {}

WorkShiftProcess::~WorkShiftProcess() {
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

void WorkShiftProcess::Behavior() {
    auto* stores = program->stores;
    auto args = program->args;

    //
    while (args->breads > 0) {
        DEBUG_PRINT("WorkShiftProcess breads_tbd: %d\n", get_breads_tbd(program->args));
        Enter(*stores->mixing, args->mixers);
        (new MixProcess(this->program, get_breads_tbd(args)))->Activate();
        args->breads -= get_breads_tbd(args);
    }

    // Wait for all processes to finish
    //    DEBUG_PRINT("Wait 1%s\n", "");
    Enter(*stores->mixing, stores->mixing->Capacity());
    //    DEBUG_PRINT("Wait 2%s\n", "");
    Leave(*stores->mixing, stores->mixing->Capacity());
    //    DEBUG_PRINT("Wait 3%s\n", "");
}

/******************************************************************************
 * MixProcess
 *****************************************************************************/
MixProcess::MixProcess(Program* _program, const int _breads_tbd) : breads_tbd(_breads_tbd), program(_program) {}

MixProcess::~MixProcess() = default;

void MixProcess::Behavior() {
    DEBUG_PRINT("MixProcess breads_tbd: %d\n", breads_tbd);

    //
    const double duration =
        Normal(mix_mean_duration_per_bread_sec * breads_tbd, mix_deviation_duration_per_bread_sec * breads_tbd);
    (*program->stats->mix_duration)(duration);
    Wait(duration);

    // Continue mixing
    if (breads_tbd == (int)program->args->mixer_capacity) {
        DEBUG_PRINT("Leave Mix%s\n", "");
        Leave(*(program)->stores->mixing, 1);
    }

    // Start Cutting after dough is mixed
    Enter(*program->stores->cutting, program->args->tables);
    (new CutProcess(this->program, breads_tbd))->Activate();
}

/******************************************************************************
 * CutProcess
 *****************************************************************************/
CutProcess::CutProcess(Program* _program, const int _breads_tbd) : breads_tbd(_breads_tbd), program(_program) {}

CutProcess::~CutProcess() = default;

void CutProcess::Behavior() {
    DEBUG_PRINT("CutProcess breads_tbd: %d\n", breads_tbd);
    //
    const double duration =
        Normal(cut_mean_duration_per_bread_sec * breads_tbd, cut_deviation_duration_per_bread_sec * breads_tbd);
    (*program->stats->cut_duration)(duration);
    Wait(duration);

    //
    Leave(*this->program->stores->cutting, 1);

    // Start Fermentation after all mixed dough is cut
    Enter(*program->stores->fermenting, program->args->fermentations);
    (new FermentationProcess(this->program, breads_tbd))->Activate();
}

/******************************************************************************
 * FermentationProcess
 *****************************************************************************/
FermentationProcess::FermentationProcess(Program* _program, const int _breads_tbd)
    : breads_tbd(_breads_tbd), program(_program) {}

FermentationProcess::~FermentationProcess() = default;

void FermentationProcess::Behavior() {
    DEBUG_PRINT("FermentationProcess breads_tbd: %d\n", breads_tbd);
    // Fermentation bunch of breads
    const double duration =
        Normal(fermentation_mean_duration_per_bread_sec, fermentation_deviation_duration_per_bread_sec);
    (*program->stats->fermentation_duration)(duration);
    Wait(duration);

    //
    Leave(*this->program->stores->fermenting, 1);

    //     Start Baking after one heap of mixed dough is fermented
    Enter(*program->stores->baking, program->args->ovens);
    (new BakeProcess(this->program, breads_tbd))->Activate();
}

/******************************************************************************
 * BakeProcess
 *****************************************************************************/
BakeProcess::BakeProcess(Program* _program, const int _breads_tbd) : breads_tbd(_breads_tbd), program(_program) {}

BakeProcess::~BakeProcess() = default;

void BakeProcess::Behavior() {
    DEBUG_PRINT("BakeProcess breads_tbd: %d\n", breads_tbd);
    //
    double duration = Normal(bake_duration_mean_per_break_sec, bake_duration_deviation_per_bread_sec);
    (*program->stats->bake_duration)(duration);
    Wait(duration);

    //
    Leave(*this->program->stores->baking, program->args->ovens);

    // Start Loading after one heap of mixed dough is baked
    Enter(*program->stores->loading, 1);
    (new LoadProcess(this->program, breads_tbd))->Activate();
}

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
    Leave(*program->stores->loading, 1);

    // Leave the bakery after all breads are loaded
    if (breads_tbd < (int)program->args->mixer_capacity) {
        DEBUG_PRINT("Leave Mix%s\n", "");
        Leave(*(program)->stores->mixing, 1);
    }
}
