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
    size_t breads = 100;
    size_t mixers = 1;
    size_t tables = 1;
    size_t fermentations = 2;
    size_t ovens = 1;
    size_t loads = 1;
    size_t simulations = 1;

    //
    const size_t mixer_capacity = 140;
    const size_t cart_capacity = 70;

    /////////////////////////
    // System Data
    /////////////////////////
    // Times
    const size_t time_baking_sec = 30 * 60;         // TODO: Time to bake 1 bread
    const size_t time_fermentation_sec = 20 * 60;   // TODO: Time to fermentation for 1 bread
    const size_t time_mixing_sec = 10 * 60;         // TODO: Time to mix dough for 100 loaves of bread
    const size_t time_make_loaf_sec = 1 * 60;       // TODO: Time to make 1 loaf of bread from dough
    const size_t time_move_carriage_sec = 2 * 60;   // TODO: Time to move carriage with loaves of bread between stages
    const size_t time_loading_box_sec = 0.25 * 60;  // TODO: Time to loads boxes with bread to the truck
    const size_t time_unloading_sec = 0.25 * 60;    // TODO: Time to unload boxes from truck
    const size_t time_work_shift_sec = 8 * 60 * 60;
};

#endif  // SRC_ARGS_H_
