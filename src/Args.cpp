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
        } else if (string(argv[i]) == string("-mc") || string(argv[i]) == string("--mixers")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> mixers;
        } else if (string(argv[i]) == string("-mcap") || string(argv[i]) == string("--mixer-capacity")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> mixer_capacity;
        } else if (string(argv[i]) == string("-oc") || string(argv[i]) == string("--ovens")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> ovens;
        } else if (string(argv[i]) == string("-fc") || string(argv[i]) == string("--fermentation-rooms")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> fermentation_rooms;
        } else if (string(argv[i]) == string("-fcap") || string(argv[i]) == string("--fermentation-room-capacity")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> fermentation_room_carriage_capacity;
        } else if (string(argv[i]) == string("-t") || string(argv[i]) == string("--tables")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> tables;
        } else if (string(argv[i]) == string("-b") || string(argv[i]) == string("--breads")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> breads;
        } else if (string(argv[i]) == string("-s") || string(argv[i]) == string("--simulations")) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> simulations;
        } else {
            print_help_exit(ExitCodes_BAD_ARGUMENTS);
        }
    }
}
void Args::debug_args() const {
    //
    std::cout << "outfile: " << outfile << std::endl;

    std::cout << "mixers: " << mixers << std::endl;
    std::cout << "mixer_capacity: " << mixer_capacity << std::endl;
    std::cout << "ovens: " << ovens << std::endl;

    std::cout << "fermentation_rooms: " << fermentation_rooms << std::endl;
    std::cout << "fermentation_room_carriage_capacity: " << fermentation_room_carriage_capacity << std::endl;
    std::cout << "tables: " << tables << std::endl;
    std::cout << "breads: " << breads << std::endl;
    std::cout << "simulations: " << simulations << std::endl;
    //
    std::cout << "time_baking_sec: " << time_baking_sec << std::endl;
    std::cout << "time_fermentation_sec: " << time_fermentation_sec << std::endl;
    std::cout << "time_mixing_sec: " << time_mixing_sec << std::endl;
    std::cout << "time_make_loaf_sec: " << time_make_loaf_sec << std::endl;
    std::cout << "time_move_carriage_sec: " << time_move_carriage_sec << std::endl;
    std::cout << "time_loading_box_sec: " << time_loading_box_sec << std::endl;
    std::cout << "time_unloading_sec: " << time_unloading_sec << std::endl;
}
