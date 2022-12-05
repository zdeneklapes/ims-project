/**
 * IMS-PROJECT VUT FIT - Bakery
 *
 * @file utils.h
 * @author Zdenek Lapes (xlapes02)
 * @author Andrej Binovsky (xbinov00)
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <iostream>
#include <random>
#include <string>

#include "ExitCodes.h"

void print_help_exit(ExitCodes exit_code);

size_t get_carts_tbd(const size_t breads_tbd, const size_t cart_capacity);

#endif  // SRC_UTILS_H_
