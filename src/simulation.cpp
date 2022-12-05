/**
 * IMS-PROJECT VUT FIT - Bakery
 *
 * @file simulation.cpp
 * @author Zdenek Lapes (xlapes02)
 * @author Andrej Binovsky (xbinov00)
 */

#include "simulation.h"

void simulate(Program *program) {
    auto &args = *program->args;

    if (!args.outfile.empty()) {
        SetOutput(args.outfile.c_str());
    }

    for (u_int64_t i = 1; i <= args.simulations; ++i) {
#if !TEST
        Print("========== %d. START Simulation (%d loaves of bread) ==========\n", i, args.breads);
#endif
        //
        Init(Args::WORK_TIME_START_SEC, Args::WORK_TIME_END_SEC);
        auto *order_process = new OrderProcess(program);
        order_process->Activate();
        Run();

#if !TEST
        SIMLIB_statistics.Output();
        Print("\n========== %d. END Simulation ==========\n\n", i);
#endif
    }
}
