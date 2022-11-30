#include "Processes.h"

//                  mixer+ovens+
Facility facilities[1 + 1 + 1 + 1 + 1];

/******************************************************************************
 * WorkShiftProcess
 *****************************************************************************/
WorkShiftProcess::WorkShiftProcess(Program& _program) : program(_program) {}

WorkShiftProcess::~WorkShiftProcess() = default;

void WorkShiftProcess::Behavior() {
    while (this->program.args.breads > 0) {
        (new MixProcess(this->program))->Activate();

        // TODO: Mix

        // TODO: Cut

        // TODO: Fermentation

        // TODO: Bake

        // TODO: Pack

        // TODO: Load
    }
}

/******************************************************************************
 * BakeProcess
 *****************************************************************************/
BakeProcess::BakeProcess(Program& _program) : bake_duration(new Stat("Bake duration")), program(_program) {}

BakeProcess::~BakeProcess() { delete bake_duration; }

void BakeProcess::Behavior() {
    double duration = Normal(bake_duration_mean_sec, bake_duration_deviation_sec);
    (*bake_duration)(duration);
}

/******************************************************************************
 * FermentationProcess
 *****************************************************************************/
FermentationProcess::FermentationProcess(Program& _program)
    : fermentation_duration(new Stat("Bread fermentation duration")), program(_program) {
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
 * MixProcess
 *****************************************************************************/
MixProcess::MixProcess(Program& _program) : mix_duration(new Stat("Mixing duration")), program(_program) {}

MixProcess::~MixProcess() { delete mix_duration; }

void MixProcess::Behavior() {
    const double duration = Normal(mix_duration_mean_per_cart_sec, mix_duration_deviation_per_cart_sec);
    (*mix_duration)(duration);
}

/******************************************************************************
 * CutProcess
 *****************************************************************************/
CutProcess::CutProcess(Program& _program) : cutting_duration(new Stat("Cutting Duration")), program(_program) {}

CutProcess::~CutProcess() { delete cutting_duration; }

void CutProcess::Behavior() {
    //
}
