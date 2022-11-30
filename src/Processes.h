#ifndef SRC_PROCESSES_H_
#define SRC_PROCESSES_H_

#include <iostream>
#include <random>
#include <string>

#include "Program.h"
#include "simlib.h"

class WorkShiftProcess : public Process {
   public:  // NOLINT
    explicit WorkShiftProcess(Program &_program);
    ~WorkShiftProcess() override = default;

    void Behavior() override;

   private:
    Program program;
};

class FermentationProcess : public Process {
   public:  // NOLINT
    explicit FermentationProcess(Program &_program);
    ~FermentationProcess() override;
    void Behavior() override;

   private:  // NOLINT
    Stat *fermentation_duration;
    Program program;
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
