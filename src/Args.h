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
    Args(int argc, char *argv[]);
    Args(const Args &);
    ~Args();

    /////////////////////////
    // Methods
    /////////////////////////
    static size_t get_breads_tbd(const size_t &_breads, const size_t &_mixer_capacity);

    /////////////////////////
    // System inputs
    /////////////////////////
    std::string outfile;
    const size_t test_value = 1;

    // Editable Capacities
    size_t breads = 200;
    size_t mixers = test_value;
    size_t tables = test_value;
    size_t fermentations = test_value + 1;  // TODO: error if fermentations < 2
    size_t ovens = test_value;
    size_t loads = test_value;
#if TEST
    size_t simulations = 1;
#else
    size_t simulations = 3;
#endif

    // Not editable Capacities
    const size_t mixer_capacity = 140;
    const size_t cart_capacity = 70;

    constexpr static const double WORK_TIME_START_SEC = 0;
    constexpr static const double WORK_TIME_END_SEC = 8 * 60 * SECONDS_PER_MINUTE;  // 8 hours: work time
};

#endif  // SRC_ARGS_H_
