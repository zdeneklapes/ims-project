//
// Created by Zdeněk Lapeš on 11/11/2022.
//

#ifndef SRC_SIMULATION_H_
#define SRC_SIMULATION_H_
#include <simlib.h>

#include <iostream>
#include <string>

#include "Args.h"
#include "Processes.h"
#include "Program.h"

/**
 * @brief Function that simulate implemented system using Simlib library
 *
 * @param program Program*
 */
void simulate(Program *program);

#endif  // SRC_SIMULATION_H_
