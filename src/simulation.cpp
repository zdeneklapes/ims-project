//
// Created by Zdeněk Lapeš on 11/11/2022.
//

#include "simulation.h"

void simulate(Program &program) {
    Args &args = program.args;

    for (int i = 0; i < args.simulations; ++i) {
        std::cout << i << ". Simulation\n";
        //        Store store(args);
        std::cout << Uniform(0, 1) << std::endl;
    }
}
