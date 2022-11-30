#include "Processes.h"

void WorkShiftProcess::Behavior() {
    // TODO: While not all breads are baked, keep baking breads.
    while (true) {
        break;
    }
}

void BakeProcess::Behavior() {
    // TODO: implement
    double duration = Normal(bake_duration_mean_sec, bake_duration_deviation_sec);
    (*bake_duration)(duration);
}

void FermentationProcess::Behavior() {
    // TODO: implement
}

void MixProcess::Behavior() {
    // TODO: implement
}
