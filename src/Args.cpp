#include "Args.h"

Args::Args(int argc, char *argv[]) {
    // TODO: handle ExitCodes_BAD_ARGUMENTS like e.q. not a number

    using namespace std;  // NOLINT

    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == string("-h") || string(argv[i]) == string("--help")) {
            print_help_exit(ExitCodes_OK);
        } else if (string(argv[i]) == string("-o") || string(argv[i]) == string("--outfile")) {
            CHECK_NEXT_ARG(argc, i);
            outfile = argv[++i];
        } else if (string(argv[i]) == string("-b") || string(argv[i]) == string("--breads")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> breads;
        } else if (string(argv[i]) == string("-m") || string(argv[i]) == string("--mixers")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> mixers;
        } else if (string(argv[i]) == string("-t") || string(argv[i]) == string("--tables")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> tables;
        } else if (string(argv[i]) == string("-f") || string(argv[i]) == string("--fermentation-rooms")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> fermentations;
        } else if (string(argv[i]) == string("--ovens")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> ovens;
        } else if (string(argv[i]) == string("-l") || string(argv[i]) == string("--loads")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> loads;
        } else if (string(argv[i]) == string("-s") || string(argv[i]) == string("--simulations")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> simulations;
        } else {
            print_help_exit(ExitCodes_BAD_ARGUMENTS);
        }
    }
}
