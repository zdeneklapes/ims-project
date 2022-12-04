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
        } else if (string(argv[i]) == string("-f") || string(argv[i]) == string("--fermentations")) {
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

Args::Args(const Args &args) {
    outfile = args.outfile;
    breads = args.breads;
    mixers = args.mixers;
    tables = args.tables;
    fermentations = args.fermentations;
    ovens = args.ovens;
    loads = args.loads;
    simulations = args.simulations;
}

Args::~Args() = default;

size_t Args::get_breads_tbd(const size_t &_breads, const size_t &_mixer_capacity) {
    return (_breads > _mixer_capacity) ? _mixer_capacity : _breads;
}
