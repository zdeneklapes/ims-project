#include "Processes.h"

int get_breads_tbd(Args* args) { return args->breads > args->mixer_capacity ? args->mixer_capacity : args->breads; }

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

    //
    std::stringstream msg;
    msg << "Total baking time: "
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
    while (args->breads > 0) {
        args->breads -= get_breads_tbd(args);
        Enter(*stores->mixing, args->mixers);
        (new MixProcess(this->program))->Activate();
    }

    Enter(*stores->mixing, stores->mixing->Capacity());
    (new MixProcess(this->program))->Activate();
}

/******************************************************************************
 * MixProcess
 *****************************************************************************/
MixProcess::MixProcess(Program* _program) : program(_program) {}

MixProcess::~MixProcess() = default;

void MixProcess::Behavior() {
    const double duration = Normal(mix_mean_duration_per_bread_sec, mix_deviation_duration_per_bread_sec);
    (*program->stats->mix_duration)(duration);
    Wait(duration);
    LEAVE_MIXING(program, program->args->breads > 0);  // Wait until all loaves of breads are baked

    // Start Cutting after dough is mixed
    Enter(*program->stores->cutting, program->args->tables);
    (new CutProcess(this->program))->Activate();
}

/******************************************************************************
 * CutProcess
 *****************************************************************************/
CutProcess::CutProcess(Program* _program) : program(_program) {}

CutProcess::~CutProcess() = default;

void CutProcess::Behavior() {
    for (u_int64_t i = 0; i < program->args->mixer_capacity; ++i) {
        const double duration = Normal(cut_mean_duration_per_bread_sec, cut_deviation_duration_per_bread_sec);
        (*program->stats->cut_duration)(duration);
        Wait(duration);
    }

    Leave(*this->program->stores->cutting, 1);

    // Start Fermentation after all mixed dough is cut
    Enter(*program->stores->fermenting, program->args->fermentations);
    (new FermentationProcess(this->program))->Activate();
}

/******************************************************************************
 * FermentationProcess
 *****************************************************************************/
FermentationProcess::FermentationProcess(Program* _program) : program(_program) {}

FermentationProcess::~FermentationProcess() = default;

void FermentationProcess::Behavior() {
    const double duration =
        Normal(fermentation_mean_duration_per_bread_sec, fermentation_deviation_duration_per_bread_sec);
    (*program->stats->fermentation_duration)(duration);
    Wait(duration);
    Leave(*this->program->stores->fermenting, 1);

    //     Start Baking after one heap of mixed dough is fermented
    Enter(*program->stores->baking, program->args->ovens);
    (new BakeProcess(this->program))->Activate();
}

/******************************************************************************
 * BakeProcess
 *****************************************************************************/
BakeProcess::BakeProcess(Program* _program) : program(_program) {}

BakeProcess::~BakeProcess() = default;

void BakeProcess::Behavior() {
    double duration = Normal(bake_duration_mean_per_break_sec, bake_duration_deviation_per_bread_sec);
    (*program->stats->bake_duration)(duration);
    Wait(duration);
    Leave(*this->program->stores->baking, program->args->ovens);

    // Start Loading after one heap of mixed dough is baked
    Enter(*program->stores->loading, 1);
    (new LoadProcess(this->program))->Activate();
}

/******************************************************************************
 * LoadProcess
 *****************************************************************************/
LoadProcess::LoadProcess(Program* _program) : program(_program) {}

LoadProcess::~LoadProcess() = default;

void LoadProcess::Behavior() {
    for (u_int64_t i = 0; i < program->args->mixer_capacity; ++i) {
        const double duration = Normal(load_mean_duration_per_bread_sec, load_deviation_duration_per_bread_sec);
        (*program->stats->load_duration)(duration);
        Wait(duration);
    }
    Leave(*this->program->stores->loading, 1);
    LEAVE_MIXING(program, program->args->breads == 0);  // Wait until all loaves of breads are baked
}
