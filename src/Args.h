#ifndef SRC_ARGS_H_
#define SRC_ARGS_H_

#include <iostream>
#include <sstream>
#include <string>

#include "Errors.h"
#include "macros.h"
#include "simlib.h"
#include "utils.h"

struct Args {
    Args(int argc, char *argv[]);
    ~Args();
    //
    uint16_t workers = 1;
    //
    uint16_t mixers = 1;
    uint16_t mixer_capacity = 100;
    //
    uint16_t breads = 100;
    //
    uint16_t ovens = 1;
    uint16_t oven_capacity = 1;
    //
    uint16_t fermentation_rooms = 1;
    uint16_t fermentation_room_capacity = 50;
    //
    std::string outfile = "bread_factory.out";
};

#endif  // SRC_ARGS_H_
