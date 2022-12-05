#ifndef SRC_ARGS_H_
#define SRC_ARGS_H_

#include <simlib.h>

#include <iostream>
#include <sstream>
#include <string>

#include "ExitCodes.h"
#include "macros.h"
#include "utils.h"

struct Args {
   public:  // NOLINT
    /**
     * @brief Construct a new Args object
     * @param argc
     * @param argv
     */
    Args(int argc, char *argv[]);

    /**
     * @brief Construct a new Args object (copy constructor)
     *
     * @param args
     */
    Args(const Args &);

    /**
     * @brief Destroy the Args object
     *
     */
    ~Args();

    /////////////////////////
    // Methods
    /////////////////////////
    static size_t get_breads_tbd(const size_t &_breads, const size_t &_mixer_capacity);

    /////////////////////////
    // System inputs
    /////////////////////////
    std::string outfile;  // Output file

    // Editable Capacities
    size_t breads = 100;       // Number of breads to be produced
    size_t mixers = 2;         // Number of mixers
    size_t tables = 2;         // Number of tables
    size_t fermentations = 8;  // Number of fermentation rooms
    size_t ovens = 2;          // Number of ovens
    size_t loads = 2;          // Number of persons loading breads into the boxes
#if TEST
    size_t simulations = 1;  // Number of simulations
#elif DEBUG
    size_t simulations = 1;  // Number of simulations
#else
    size_t simulations = 3;  // Number of simulations
#endif

    // Not editable Capacities
    const size_t mixer_capacity = 140;                                              // Capacity of one mixer
    const size_t cart_capacity = 70;                                                // Capacity of one cart
    constexpr static const double WORK_TIME_START_SEC = 0;                          //
    constexpr static const double WORK_TIME_END_SEC = 8 * 60 * SECONDS_PER_MINUTE;  // 8 hours: work time
};

#endif  // SRC_ARGS_H_
