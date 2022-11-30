#include "Processes.h"

/******************************************************************************
 * WorkShiftProcess
 *****************************************************************************/
void WorkShiftProcess::Behavior() {
    // TODO: While not all breads are baked, keep baking breads.
    while (true) {
        break;
    }
}
WorkShiftProcess::WorkShiftProcess(Program& _program) : program(_program) {
    //
}

/******************************************************************************
 * BakeProcess
 *****************************************************************************/
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
void MixProcess::Behavior() {
    // TODO: implement
}
