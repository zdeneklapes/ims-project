//
// Created by Zdeněk Lapeš on 11/11/2022.
//

#include "Args.h"
#include "Program.h"
#include "simulation.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    Args args(argc, argv);
    Program program(args);

    //
    simulate(program);

    //
    return 0;
}
