#ifndef SRC_PROCESSES_H_
#define SRC_PROCESSES_H_

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
    explicit MixProcess(Program *_program, const int _breads_tbd);
    ~MixProcess() override;
    void Behavior() override;

   private:
    // Data
    const double mix_mean_duration_per_bread_sec = 0.5 * SECONDS_PER_MINUTE;
    const double mix_deviation_duration_per_bread_sec = 0.1 * SECONDS_PER_MINUTE;
    const int breads_tbd;

    //
    Program *program;
};

class CutProcess : public Process {
   public:
    explicit CutProcess(Program *_program, const int _breads_tbd);
    ~CutProcess() override;
    void Behavior() override;

   private:
    // Data
    const double cut_mean_duration_per_bread_sec = 0.5 * SECONDS_PER_MINUTE;
    const double cut_deviation_duration_per_bread_sec = 0.1 * SECONDS_PER_MINUTE;
    const int breads_tbd;

    //
    Program *program;
};

class FermentationProcess : public Process {
   public:
    explicit FermentationProcess(Program *_program, const int _breads_tbd);
    ~FermentationProcess() override;
    void Behavior() override;

   private:
    // Data
    const double fermentation_mean_duration_per_bread_sec = 20 * SECONDS_PER_MINUTE;
    const double fermentation_deviation_duration_per_bread_sec = 1 * SECONDS_PER_MINUTE;
    const int breads_tbd;

    //
    Program *program;
};

class BakeProcess : public Process {
   public:
    explicit BakeProcess(Program *_program, const int _breads_tbd);
    ~BakeProcess() override;
    void Behavior() override;

   private:
    // Data
    const double bake_duration_mean_per_break_sec = 30 * SECONDS_PER_MINUTE;
    const double bake_duration_deviation_per_bread_sec = 3 * SECONDS_PER_MINUTE;
    const int breads_tbd;

    //
    Program *program;
};

class LoadProcess : public Process {
   public:
    explicit LoadProcess(Program *_program, const int _breads_tbd);
    ~LoadProcess() override;
    void Behavior() override;

   private:
    // Data
    const double load_mean_duration_per_bread_sec = 0.25 * SECONDS_PER_MINUTE;
    const double load_deviation_duration_per_bread_sec = 0.1 * SECONDS_PER_MINUTE;
    const int breads_tbd;

    //
    Program *program;
};

#endif  // SRC_PROCESSES_H_
