#ifndef SRC_PROCESSES_H_
#define SRC_PROCESSES_H_

#include <iostream>
#include <random>
#include <string>

#include "Program.h"
#include "simlib.h"

Store worker_capacity = Store("Worker capacity", 5);  // default

class WorkShiftProcess : public Process {
   public:
    explicit WorkShiftProcess(Program &_program);
    ~WorkShiftProcess() override;

    void Behavior() override;

   private:
    Program program;
};

class FermentationProcess : public Process {
   public:
    explicit FermentationProcess(Program &_program);
    ~FermentationProcess() override;
    void Behavior() override;

   private:
    //
    Stat *fermentation_duration;
    Store fermentation_capacity = Store("Fermentation capacity", 1 * 8);  // default (1 fermentation room * 8 carts)

    //
    Program program;
};

class BakeProcess : public Process {
   public:
    explicit BakeProcess(Program &_program);
    ~BakeProcess() override;
    void Behavior() override;

   private:
    //
    Stat *bake_duration{};
    Store bake_capacity = Store("Bake capacity", 1 * 8);  // default (1 oven * 8 carts)

    // Data
    const double bake_duration_mean_sec = 10 * SECONDS_PER_MINUTE;
    const double bake_duration_deviation_sec = 2 * SECONDS_PER_MINUTE;

    //
    Program program;
};

class CutProcess : public Process {
   public:
    explicit CutProcess(Program &_program);
    ~CutProcess() override;
    void Behavior() override;

   private:
    //
    Stat *cutting_duration{};
    Store cutting_capacity = Store("Cutting capacity", 1);  // default (only 1 person can make loaves of bread)

    // Data
    const double cut_duration_mean_per_cart_sec = 10 * SECONDS_PER_MINUTE;
    const double cut_duration_deviation_per_cart_sec = 2 * SECONDS_PER_MINUTE;

    //
    Program program;
};

class MixProcess : public Process {
   public:
    explicit MixProcess(Program &_program);
    ~MixProcess() override;
    void Behavior() override;

   private:
    //
    Stat *mix_duration;
    Store mixer_capacity = Store("Mixer capacity", 1);  // default (1 mixer available)

    // Data
    const double mix_duration_mean_per_cart_sec = 10 * SECONDS_PER_MINUTE;
    const double mix_duration_deviation_per_cart_sec = 4 * SECONDS_PER_MINUTE;

    //
    Program program;
};

#endif  // SRC_PROCESSES_H_
