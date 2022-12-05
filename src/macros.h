/**
 * IMS-PROJECT VUT FIT - Bakery
 *
 * @file macros.h
 * @author Zdenek Lapes (xlapes02)
 * @author Andrej Binovsky (xbinov00)
 */

#ifndef SRC_MACROS_H_
#define SRC_MACROS_H_

#include <cstdio>

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define SECONDS_PER_MINUTE 60

#define CHECK_NEXT_ARG(argc, i)                       \
    do {                                              \
        if (!((i) + 1 < (argc))) {                    \
            print_help_exit(ExitCodes_BAD_ARGUMENTS); \
        }                                             \
    } while (0);

#define LEAVE_MIXING(program, condition)          \
    do {                                          \
        if ((condition)) {                        \
            Leave(*(program)->stores->mixing, 1); \
        }                                         \
    } while (0);

/*******************************************************************************
 * Macros Debug
 ******************************************************************************/
#define DEBUG 0
#define TEST 0
#define DEBUG_PRINT(fmt, ...)                                                               \
    do {                                                                                    \
        if (DEBUG) {                                                                        \
            fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
        }                                                                                   \
    } while (0)

#endif  // SRC_MACROS_H_
