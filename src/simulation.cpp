//
// Created by Zdeněk Lapeš on 11/11/2022.
//

#include "simulation.h"

#include "Processes.h"

void simulate(Program &program) {
    Args &args = program.args;

    for (int i = 0; i < args.simulations; ++i) {
        //
        std::cout << "=== " << i << ". START Simulation ===\n";

        //
        Init(0, static_cast<double>(args.time_work_shift_sec));
        (new WorkShiftProcess(program))->Activate();
        Run();
        SIMLIB_statistics.Output();

        //
        std::cout << "=== " << i << ". END Simulation ===\n";
    }
}
