/**
 * IMS-PROJECT VUT FIT - Bakery
 *
 * @file experiments.h
 * @author Zdenek Lapes (xlapes02)
 * @author Andrej Binovsky (xbinov00)
 */

#ifndef SRC_EXPERIMENTS_H_
#define SRC_EXPERIMENTS_H_

#include <algorithm>
#include <string>
#include <vector>

#include "Program.h"
#include "macros.h"
#include "simulation.h"

class TestResult {
   public:
    TestResult(const size_t _mixers, const size_t _tables, const size_t _fermentations, const size_t _ovens,
               const size_t _loads, const size_t _simulations, const size_t _breads, const size_t _mixer_capacity,
               const size_t _cart_capacity, const size_t _simulation_time);
    ~TestResult();
    const size_t mixers;
    const size_t tables;
    const size_t fermentations;
    const size_t ovens;
    const size_t loads;
    const size_t breads;
    const size_t simulations;
    const size_t mixer_capacity;
    const size_t cart_capacity;
    const double simulation_time;
};

/**
 * @brief Function that prints out the results of the simulation
 * @param results
 */
void print_test_result(std::vector<TestResult *> &results);

/**
 * @brief Function that test try to find the optimum number of all Facilities & Stores and its capacitites modelled in
 * the system
 *
 * @param program Program*
 */
void experiments(Program *program);

#endif  // SRC_EXPERIMENTS_H_
