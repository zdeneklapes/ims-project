#include "Args.h"

Args::Args(int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_help_exit();
        }
        if (strcmp(argv[i], "--outfile") == 0 || strcmp(argv[i], "-o") == 0) {
            CHECK_NEXT_ARG(argc, i);
            outfile = argv[++i];
        }
        if (strcmp(argv[i], "--mixers") == 0 || strcmp(argv[i], "-mc") == 0) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> mixers;
        }
        if (strcmp(argv[i], "--mixer-capacity") == 0 || strcmp(argv[i], "-mc") == 0) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> mixers;
        }
        if (strcmp(argv[i], "--ovens") == 0 || strcmp(argv[i], "-oc") == 0) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> ovens;
        }
        if (strcmp(argv[i], "--oven-space") == 0 || strcmp(argv[i], "-os") == 0) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> ovens;
        }
        if (strcmp(argv[i], "--fermentation-rooms") == 0 || strcmp(argv[i], "-fr") == 0) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> fermentation_rooms;
        }
        if (strcmp(argv[i], "--fermentation-room-capacity") == 0 || strcmp(argv[i], "-frc") == 0) {
            CHECK_NEXT_ARG(argc, i);
            std::stringstream(argv[++i]) >> fermentation_room_capacity;
        }
    }
}
