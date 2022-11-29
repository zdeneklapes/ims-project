//
// Created by Zdeněk Lapeš on 29/11/2022.
//

#ifndef SRC_PROGRAM_H_
#define SRC_PROGRAM_H_
#include "Args.h"

struct Program {
    explicit Program(Args &args);
    ~Program() = default;
    Args args;
};
#endif  // SRC_PROGRAM_H_
