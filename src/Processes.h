#ifndef SRC_PROCESSES_H_
#define SRC_PROCESSES_H_

#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "Program.h"
#include "simlib.h"

class OrderProcess : public Process {
   public:
    explicit OrderProcess(Program *_program);
    ~OrderProcess() override;

    void Behavior() override;

   private:
    Program *program;
};

class MixProcess : public Process {
   public:
    MixProcess(Program *_program, const size_t _breads_tbd);
    ~MixProcess() override;
    void Behavior() override;

   private:
    // Data
    const double mix_mean_duration_per_bread_sec = 0.5 * SECONDS_PER_MINUTE;
    const double mix_deviation_duration_per_bread_sec = 0.2 * SECONDS_PER_MINUTE;

    //
    Program *program;
    const size_t breads_tbd;
};

class CutProcess : public simlib3::Process {
   public:
    CutProcess(Program *_program, const size_t _breads_tbd);
    ~CutProcess() override;
    void Behavior() override;

   private:
    // Data
    const double cut_mean_duration_per_bread_sec = 0.5 * SECONDS_PER_MINUTE;
    const double cut_deviation_duration_per_bread_sec = 0.2 * SECONDS_PER_MINUTE;
    const size_t breads_tbd;

    //
    Program *program;
};

class FermentationProcess : public simlib3::Process {
   public:
    FermentationProcess(Program *_program, const size_t _breads_tbd);
    ~FermentationProcess() override;
    void Behavior() override;

   private:
    // Data
    const double fermentation_mean_duration_per_bread_sec = 20 * SECONDS_PER_MINUTE;
    const double fermentation_deviation_duration_per_bread_sec = 5 * SECONDS_PER_MINUTE;

    //
    Program *program;
    const size_t breads_tbd;
};

class BakeProcess : public simlib3::Process {
   public:
    BakeProcess(Program *_program, const size_t _breads_tbd);
    ~BakeProcess() override;
    void Behavior() override;

   private:
    // Data
    const double bake_duration_mean_per_break_sec = 30 * SECONDS_PER_MINUTE;
    const double bake_duration_deviation_per_bread_sec = 10 * SECONDS_PER_MINUTE;

    //
    Program *program;
    const size_t breads_tbd;
};

class LoadProcess : public Process {
   public:
    LoadProcess(Program *_program, const size_t _breads_tbd);
    ~LoadProcess() override;
    void Behavior() override;

   private:
    // Data
    const double load_mean_duration_per_bread_sec = 0.25 * SECONDS_PER_MINUTE;
    const double load_deviation_duration_per_bread_sec = 0.2 * SECONDS_PER_MINUTE;

    //
    Program *program;
    const size_t breads_tbd;
};

#endif  // SRC_PROCESSES_H_
