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

    //
    void debug_args() const;

    /////////////////////////
    // System inputs
    /////////////////////////
    // Order
    uint64_t breads = 10;
    //
    uint64_t mixers = 1;
    uint64_t mixer_capacity = 50;
    //
    uint64_t tables = 1;
    uint64_t table_capacity = 1;
    //
    uint64_t ovens = 1;
    uint64_t oven_capacity = 50;
    //
    uint64_t fermentations = 1;
    uint64_t fermentation_capacity = 50;
    //
    uint64_t simulations = 1;
    //
    std::string outfile;

    /////////////////////////
    // System Data
    /////////////////////////
    // Times
    u_int64_t time_baking_sec = 30 * 60;          // TODO: Time to bake 1 bread
    u_int64_t time_fermentation_sec = 20 * 60;    // TODO: Time to fermentation for 1 bread
    u_int64_t time_mixing_sec = 10 * 60;          // TODO: Time to mix dough for 100 loaves of bread
    u_int64_t time_make_loaf_sec = 1 * 60;        // TODO: Time to make 1 loaf of bread from dough
    u_int64_t time_move_carriage_sec = 2 * 60;    // TODO: Time to move carriage with loaves of bread between stages
    u_int64_t time_loading_box_sec = 0.25 * 60;   // TODO: Time to load boxes with bread to the truck
    u_int64_t time_unloading_sec = 0.25 * 60;     // TODO: Time to unload boxes from truck
    u_int64_t time_work_shift_sec = 8 * 60 * 60;  // TODO: Time work shift
};

#endif  // SRC_ARGS_H_
