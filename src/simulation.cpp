//
// Created by Zdeněk Lapeš on 11/11/2022.
//

#include "simulation.h"

double simulate(Program *program) {
    auto &args = *program->args;

    if (!args.outfile.empty()) {
        SetOutput(args.outfile.c_str());
    }

    for (u_int64_t i = 0; i < args.simulations; ++i) {
#if !TEST
        Print("========== %d. START Simulation (%d loaves of bread) ==========\n", i, args.breads);
#endif
        //
        Init(OrderTimer::ORDER_WORK_TIME_START_SEC, OrderTimer::ORDER_WORK_TIME_END_SEC);
        auto *order_process = new OrderProcess(program);
        order_process->Activate();
        Run();

#if !TEST
        SIMLIB_statistics.Output();
        Print("\n========== %d. END Simulation (%d hours) ==========\n\n", i,
              OrderTimer::ORDER_WORK_TIME_END_SEC / SECONDS_PER_MINUTE);
#endif
    }
    return program->simulation_time;
}
