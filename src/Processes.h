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
#include "utils.h"

/******************************************************************************
 * OrderProcess
 *****************************************************************************/
class OrderProcess : public Process {
   public:
    /**
     * @brief Construct a new Order Process object
     *
     * @param _program
     */
    explicit OrderProcess(Program *_program);
    /**
     * @brief Destroy the Order Process object
     *
     */
    ~OrderProcess() override;

    /**
     * @brief Implements inherited method
     *
     */
    void Behavior() override;

   private:
    Program *program;
};

/******************************************************************************
 * MixProcess
 *****************************************************************************/
class MixProcess : public Process {
   public:
    /**
     * @brief Construct a new Mix Process object
     *
     * @param _program
     * @param _breads_tbd
     */
    MixProcess(Program *_program, size_t _breads_tbd);

    /**
     * @brief Destroy the Mix Process object
     *
     */
    ~MixProcess() override;

    /**
     * @brief Implements inherited method
     *
     */
    void Behavior() override;

   private:
    /////////////////////////
    // Data about Mixing duration
    /////////////////////////
    const double mix_mi_duration_per_bread_sec = 10 * SECONDS_PER_MINUTE;
    const double mix_sigma_duration_per_bread_sec = mix_mi_duration_per_bread_sec * 0.05;

    //
    Program *program;
    const size_t breads_tbd;
};

/******************************************************************************
 * CutProcess
 *****************************************************************************/
class CutProcess : public simlib3::Process {
   public:
    /**
     * @brief Construct a new Cut Process object
     *
     * @param _program
     * @param _breads_tbd
     */
    CutProcess(Program *_program, size_t _breads_tbd);

    /**
     * @brief Destroy the Cut Process object
     *
     */
    ~CutProcess() override;
    /**
     * @brief Implements inherited method
     *
     */
    void Behavior() override;

   private:
    /////////////////////////
    // Data about Cutting duration
    /////////////////////////
    const double cut_mi_duration_per_bread_sec = 35;
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
    /**
     * @brief Construct a new Fermentation Process object
     *
     * @param _program
     * @param _breads_tbd
     */
    FermentationProcess(Program *_program, size_t _breads_tbd);

    /**
     * @brief Destroy the Fermentation Process object
     *
     */
    ~FermentationProcess() override;

    /**
     * @brief Implements inherited method
     *
     */
    void Behavior() override;

   private:
    /////////////////////////
    // Data
    /////////////////////////
    const double fermentation_mi_duration_per_bread_sec = 20 * SECONDS_PER_MINUTE;
    const double fermentation_sigma_duration_per_bread_sec = 2 * SECONDS_PER_MINUTE;

    //
    Program *program;
    const size_t breads_tbd;
};

/******************************************************************************
 * BakeProcess
 *****************************************************************************/
class BakeProcess : public simlib3::Process {
   public:
    /**
     * @brief Construct a new Bake Process object
     *
     * @param _program
     * @param _breads_tbd
     */
    BakeProcess(Program *_program, size_t _breads_tbd);

    /**
     * @brief Destroy the Bake Process object
     *
     */
    ~BakeProcess() override;

    /**
     * @brief Implements inherited method
     *
     */
    void Behavior() override;

   private:
    /////////////////////////
    // Data about Baking duration
    /////////////////////////
    const double bake_mi_duration_per_break_sec = 30 * SECONDS_PER_MINUTE;
    const double bake_sigma_duration_per_bread_sec = 2 * SECONDS_PER_MINUTE;

    //
    Program *program;
    const size_t breads_tbd;
};

/******************************************************************************
 * LoadProcess
 *****************************************************************************/
class LoadProcess : public Process {
   public:
    /**
     * @brief Construct a new Load Process object
     *
     * @param _program
     * @param _breads_tbd
     */
    LoadProcess(Program *_program, size_t _breads_tbd);

    /**
     * @brief Destroy the Load Process object
     *
     */
    ~LoadProcess() override;

    /**
     * @brief Implements inherited method
     *
     */
    void Behavior() override;

   private:
    /////////////////////////
    // Data
    /////////////////////////
    const double load_mi_duration_per_bread_sec = 12;
    const double load_sigma_duration_per_bread_sec = load_mi_duration_per_bread_sec * 0.2;
    const double prepare_boxes_mi_duration_per_bread_sec = 20;
    const double prepare_boxes_sigma_duration_per_bread_sec = prepare_boxes_mi_duration_per_bread_sec * 0.2;

    //
    Program *program;
    const size_t breads_tbd;
};

#endif  // SRC_PROCESSES_H_
