/**
 * IMS-PROJECT VUT FIT - Bakery
 *
 * @file utils.cpp
 * @author Zdenek Lapes (xlapes02)
 * @author Andrej Binovsky (xbinov00)
 */

#include "utils.h"

/**
 * Print to stdout usage of the program
 * @param exit_code enum ExitCodes
 */
void print_help_exit(ExitCodes exit_code) {
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

/**
 * @brief Get the how many loaves of bread need to be produced yet
 * @param breads_tbd
 * @param cart_capacity
 * @return size_t
 */
size_t get_carts_tbd(const size_t breads_tbd, const size_t cart_capacity) {
    return ceil((double)breads_tbd / (double)cart_capacity);
}
