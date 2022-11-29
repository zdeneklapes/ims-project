#ifndef SRC_MACROS_H_
#define SRC_MACROS_H_

#define CHECK_NEXT_ARG(argc, i)    \
    do {                           \
        if (!((i) + 1 < (argc))) { \
            print_help_exit();     \
        }                          \
    } while (0);

#endif  // SRC_MACROS_H_
