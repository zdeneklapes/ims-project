#ifndef SRC_ARGS_H_
#define SRC_ARGS_H_

#include <iostream>
#include <sstream>
#include <string>

#include "ExitCodes.h"
#include "macros.h"
#include "simlib.h"
#include "utils.h"

struct Args {
   public:  // NOLINT
    Args(int argc, char *argv[]);
    ~Args() = default;

    /////////////////////////
    // System inputs
    /////////////////////////
    std::string outfile;
    size_t breads = 1000;  // TODO: 10361 ERROR
    size_t mixers = 1;
    size_t tables = 1;
    size_t fermentations = 2;
    size_t ovens = 1;
    size_t loads = 1;
    size_t simulations = 1;

    //
    const size_t mixer_capacity = 140;
    const size_t cart_capacity = 70;

    size_t get_breads_tbd() const;
};

#endif  // SRC_ARGS_H_
