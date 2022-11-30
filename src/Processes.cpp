#include "Processes.h"

#include <z3_fixedpoint.h>

/******************************************************************************
 * WorkShiftProcess
 *****************************************************************************/
WorkShiftProcess::WorkShiftProcess(Program* _program) : program(_program) {}

WorkShiftProcess::~WorkShiftProcess() = default;

void WorkShiftProcess::Behavior() {
    auto* stores = program->stores;
    auto args = program->args;
    while (this->program->args->mixer_capacity > 0) {
        //
        Enter(*stores->mixer_capacity, 1);
        (new MixProcess(this->program))->Activate();

        //
        //        Enter(cut_capacity, 1);
        //        (new CutProcess(this->program))->Activate();

        //
        //        Enter(fermentation_capacity, 1);
        //        (new FermentationProcess(this->program))->Activate();

        //
        //        Enter(bake_capacity, 1);
        //        (new BakeProcess(this->program))->Activate();

        //
        //        Enter(load_capacity, 1);
        //        (new LoadProcess(this->program))->Activate();

        args->breads--;
    }
}

/******************************************************************************
 * MixProcess
 *****************************************************************************/
MixProcess::MixProcess(Program* _program) : mix_duration(new Stat("Mix duration")), program(_program) {}

MixProcess::~MixProcess() { delete mix_duration; }

void MixProcess::Behavior() {
    const double duration = Normal(mix_duration_mean_per_cart_sec, mix_duration_deviation_per_cart_sec);
    (*mix_duration)(duration);
    Wait(duration);
    Leave(*this->program->stores->mixer_capacity, 1);
}

#if 0

/******************************************************************************
 * CutProcess
 *****************************************************************************/
CutProcess::CutProcess(Program& _program) : cutting_duration(new Stat("Cut Duration")), program(args) {}

CutProcess::~CutProcess() { delete cutting_duration; }

void CutProcess::Behavior() {
    //
}

/******************************************************************************
 * FermentationProcess
 *****************************************************************************/
FermentationProcess::FermentationProcess(Program& _program)
    : fermentation_duration(new Stat("Fermentation duration")), program(args) {
    // TODO: implement
}

FermentationProcess::~FermentationProcess() {
    // TODO: implement
    delete fermentation_duration;
}

void FermentationProcess::Behavior() {
    // TODO: implement
}

/******************************************************************************
 * BakeProcess
 *****************************************************************************/
BakeProcess::BakeProcess(Program& _program) : bake_duration(new Stat("Bake duration")), program(args) {}

BakeProcess::~BakeProcess() { delete bake_duration; }

void BakeProcess::Behavior() {
    double duration = Normal(bake_duration_mean_sec, bake_duration_deviation_sec);
    (*bake_duration)(duration);
}

/******************************************************************************
 * LoadProcess
 *****************************************************************************/
LoadProcess::LoadProcess(Program& _program) : load_duration(new Stat("Load Duration")), program(args) {}

LoadProcess::~LoadProcess() { delete load_duration; }

void LoadProcess::Behavior() {
    //
}

#endif
