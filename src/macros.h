#ifndef SRC_MACROS_H_
#define SRC_MACROS_H_

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

#endif  // SRC_MACROS_H_
