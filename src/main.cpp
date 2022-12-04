//
// Created by Zdeněk Lapeš on 11/11/2022.
//

#include <random>

#include "Args.h"
#include "Program.h"
#include "simulation.h"
#include "test.h"

using namespace std;  // NOLINT

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    auto* args = new Args(argc, argv);
    auto* stores = new Sources(args);
    auto program = new Program(args, stores);

    //
#if TEST
    test1(program);
#else
    simulate(program);
#endif

    //
    delete program;
    return 0;
}
