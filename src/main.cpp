//
// Created by Zdeněk Lapeš on 11/11/2022.
//

#include <getopt.h>
#include <string.h>

#include <iostream>
#include <sstream>

#include "Args.h"
#include "Errors.h"
#include "macros.h"
#include "simlib.h"
#include "utils.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    Args args(argc, argv);
    return 0;
}
