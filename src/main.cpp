/**
 * IMS-PROJECT VUT FIT - Bakery
 *
 * @file main.cpp
 * @author Zdenek Lapes (xlapes02)
 * @author Andrej Binovsky (xbinov00)
 */

#include <random>

#include "Args.h"
#include "Program.h"
#include "experiments.h"
#include "simulation.h"

using namespace std;  // NOLINT

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    auto* args = new Args(argc, argv);
    auto* stores = new Sources(args);
    auto program = new Program(args, stores);

    //
#if TEST
    experiments(program);
#else
    simulate(program);
#endif

    //
    delete program;
    return 0;
}
