#ifndef SRC_PROCESSES_H_
#define SRC_PROCESSES_H_

#include <z3_fixedpoint.h>

#include <iostream>
#include <random>
#include <string>

#include "Program.h"
#include "simlib.h"

class WorkShiftProcess : public Process {
   public:
    explicit WorkShiftProcess(Program *_program);
    ~WorkShiftProcess() override;

    void Behavior() override;

   private:
    Program *program;
};

class MixProcess : public Process {
   public:
    explicit MixProcess(Program *_program);
    ~MixProcess() override;
    void Behavior() override;

   private:
    //
    Stat *mix_duration;

    // Data
    const double mix_duration_mean_per_cart_sec = 10 * SECONDS_PER_MINUTE;
    const double mix_duration_deviation_per_cart_sec = 4 * SECONDS_PER_MINUTE;

    //
    Program *program;
};

#if 0

class CutProcess : public Process {
   public:
    explicit CutProcess(Program &_program);
    ~CutProcess() override;
    void Behavior() override;

   private:
    //
    Stat *cutting_duration;

    // Data
    const double cut_duration_mean_per_cart_sec = 10 * SECONDS_PER_MINUTE;
    const double cut_duration_deviation_per_cart_sec = 2 * SECONDS_PER_MINUTE;

    //
    Program *program;
};

class FermentationProcess : public Process {
   public:
    explicit FermentationProcess(Program &_program);
    ~FermentationProcess() override;
    void Behavior() override;

   private:
    //
    Stat *fermentation_duration;

    //
    Program *program;
};


class BakeProcess : public Process {
   public:
    explicit BakeProcess(Program &_program);
    ~BakeProcess() override;
    void Behavior() override;

   private:
    //
    Stat *bake_duration;

    // Data
    const double bake_duration_mean_sec = 10 * SECONDS_PER_MINUTE;
    const double bake_duration_deviation_sec = 2 * SECONDS_PER_MINUTE;

    //
    Program *program;
};

class LoadProcess : public Process {
   public:
    explicit LoadProcess(Program &_program);
    ~LoadProcess() override;
    void Behavior() override;

   private:
    //
    Stat *load_duration;

    // Data
    const double load_duration_mean_per_cart_sec = 10 * SECONDS_PER_MINUTE;
    const double load_duration_deviation_per_cart_sec = 4 * SECONDS_PER_MINUTE;

    //
    Program *program;
};
#endif

#endif  // SRC_PROCESSES_H_
