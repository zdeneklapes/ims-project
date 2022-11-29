#include "utils.h"

void print_help_exit(uint16_t exit_code) {
    using namespace std;  // NOLINT
    cout << "USAGE:\n";
    cout << "\t-h | --help\n";
    cout << "\t-o | --outfile filename\n";
    cout << "\t-mc | --mixers count\n";
    cout << "\t-mcap | --mixer-capacity count\n";
    cout << "\t-oc | --ovens count\n";
    cout << "\t-ocap | --oven-capacity count\n";
    cout << "\t-fc | --fermentation-rooms count\n";
    cout << "\t-fcap | --fermentation-room-capacity count\n";
    exit(exit_code);
}
