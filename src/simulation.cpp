//
// Created by Zdeněk Lapeš on 11/11/2022.
//

#include "simulation.h"

#include "Processes.h"

void simulate(Program *program) {
    auto &args = *program->args;
    std::stringstream msg;

    if (!args.outfile.empty()) {
        SetOutput(args.outfile.c_str());
    }

    for (u_int64_t i = 0; i < args.simulations; ++i) {
        //
        msg.str("");  // clear
        msg << "========== " << i << ". START Simulation ==========\n";
        Print(msg.str().c_str());

        //
        Init(0, static_cast<double>(args.time_work_shift_sec));
        (new WorkShiftProcess(program))->Activate();
        Run();

        //
        SIMLIB_statistics.Output();

        //
        msg.str("");  // clear
        msg << "========== " << i << ". END Simulation ==========\n";
        Print(msg.str().c_str());
    }
}
