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
    uint16_t workers = 1;
    //
    uint16_t mixers = 1;
    uint16_t mixer_capacity = 100;
    //
    uint16_t tables = 1;
    //
    uint16_t breads = 100;
    //
    uint16_t ovens = 1;
    uint16_t oven_capacity = 1;
    //
    uint16_t fermentation_rooms = 1;
    uint16_t fermentation_room_capacity = 50;
    //
    uint16_t simulations = 1;
    //
    std::string outfile = "bread_factory.out";

    /////////////////////////
    // System Data
    /////////////////////////
    u_int64_t time_baking_sec = 30 * 60;         // TODO: Time to bake 1 bread
    u_int64_t time_fermentation_sec = 20 * 60;   // TODO: Time to fermentation for 1 bread
    u_int64_t time_mixing_sec = 10 * 60;         // TODO: Time to mix dough for 100 loaves of bread
    u_int64_t time_make_loaf_sec = 1 * 60;       // TODO: Time to make 1 loaf of bread from dough
    u_int64_t time_move_carriage_sec = 2 * 60;   // TODO: Time to move carriage with loaves of bread between stages
    u_int64_t time_loading_box_sec = 0.25 * 60;  // TODO: Time to load boxes with bread to the truck
    u_int64_t time_unloading_sec = 0.25 * 60;    // TODO: Time to unload boxes from truck
};

#endif  // SRC_ARGS_H_
