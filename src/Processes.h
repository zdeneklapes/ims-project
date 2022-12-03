#ifndef SRC_PROCESSES_H_
#define SRC_PROCESSES_H_

//
#include <simlib.h>

#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "Program.h"

//
class OrderTimer;
#include "OrderTimer.h"

/******************************************************************************
 * OrderProcess
 *****************************************************************************/
class OrderProcess : public Process {
   public:
    explicit OrderProcess(Program *_program);
    ~OrderProcess() override;

    void Behavior() override;

   private:
    Program *program;
};

/******************************************************************************
 * MixProcess
 *****************************************************************************/
class MixProcess : public Process {
   public:
    MixProcess(Program *_program, size_t _breads_tbd);
    ~MixProcess() override;
    void Behavior() override;

   private:
    // Data
    const double mix_mi_duration_per_bread_sec = 0.5 * SECONDS_PER_MINUTE;
    const double mix_sigma_duration_per_bread_sec = mix_mi_duration_per_bread_sec * 0.2;

    //
    Program *program;
    const size_t breads_tbd;
};

/******************************************************************************
 * CutProcess
 *****************************************************************************/
class CutProcess : public simlib3::Process {
   public:
    CutProcess(Program *_program, size_t _breads_tbd);
    ~CutProcess() override;
    void Behavior() override;

   private:
    // Data
    const double cut_mi_duration_per_bread_sec = 0.5 * SECONDS_PER_MINUTE;
    const double cut_sigma_duration_per_bread_sec = cut_mi_duration_per_bread_sec * 0.2;
    const size_t breads_tbd;

    //
    Program *program;
};

/******************************************************************************
 * FermentationProcess
 *****************************************************************************/
class FermentationProcess : public simlib3::Process {
   public:
    FermentationProcess(Program *_program, size_t _breads_tbd);
    ~FermentationProcess() override;
    void Behavior() override;

   private:
    // Data
    const double fermentation_mi_duration_per_bread_sec = 20 * SECONDS_PER_MINUTE;
    const double fermentation_sigma_duration_per_bread_sec = fermentation_mi_duration_per_bread_sec * 0.2;

    //
    Program *program;
    const size_t breads_tbd;
};

/******************************************************************************
 * BakeProcess
 *****************************************************************************/
class BakeProcess : public simlib3::Process {
   public:
    BakeProcess(Program *_program, size_t _breads_tbd);
    ~BakeProcess() override;
    void Behavior() override;

   private:
    // Data
    const double bake_mi_duration_per_break_sec = 30 * SECONDS_PER_MINUTE;
    const double bake_sigma_duration_per_bread_sec = bake_mi_duration_per_break_sec * 0.2;

    //
    Program *program;
    const size_t breads_tbd;
};

/******************************************************************************
 * LoadProcess
 *****************************************************************************/
class LoadProcess : public Process {
   public:
    LoadProcess(Program *_program, size_t _breads_tbd);
    ~LoadProcess() override;
    void Behavior() override;

   private:
    // Data
    const double load_mi_duration_per_bread_sec = 0.25 * SECONDS_PER_MINUTE;
    const double load_sigma_duration_per_bread_sec = load_mi_duration_per_bread_sec * 0.2;

    //
    Program *program;
    const size_t breads_tbd;
};

#endif  // SRC_PROCESSES_H_
