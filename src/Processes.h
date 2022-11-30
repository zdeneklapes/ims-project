#ifndef SRC_PROCESSES_H_
#define SRC_PROCESSES_H_

#include <iostream>
#include <random>
#include <string>

#include "simlib.h"

class WorkShiftProcess : public Process {
   public:  // NOLINT
    WorkShiftProcess() = default;
    ~WorkShiftProcess() override = default;

    void Behavior() override;
};

class FermentationProcess : public Process {
   public:  // NOLINT
    FermentationProcess() = default;
    ~FermentationProcess() override = default;
    void Behavior() override;

   private:  // NOLINT
    Stat *fermentation_duration;
};

class BakeProcess : public Process {
   public:  // NOLINT
    BakeProcess(const double _bake_duration_mean, const double _bake_duration_deviation)
        : bake_duration_mean_sec(_bake_duration_mean), bake_duration_deviation_sec(_bake_duration_deviation) {}
    ~BakeProcess() override = default;
    void Behavior() override;

   private:  // NOLINT
    Stat *bake_duration{};

    const double bake_duration_mean_sec;
    const double bake_duration_deviation_sec;
};

class MixProcess : public Process {
   public:  // NOLINT
    MixProcess() = default;
    ~MixProcess() override = default;
    void Behavior() override;

   private:  // NOLINT
    Stat *mix_duration;
};

#endif  // SRC_PROCESSES_H_
