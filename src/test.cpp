#include "test.h"

void test1(Program *program) {
    std::vector<double> results;

    for (int mixers = 1; mixers < MAX_CONSTANT; ++mixers) {
        for (int tables = 1; tables < MAX_CONSTANT; ++tables) {
            for (int fermentation_cap = 1; fermentation_cap < MAX_CONSTANT; ++fermentation_cap) {
                for (int ovens = 1; ovens < MAX_CONSTANT; ++ovens) {
                    for (int loads = 1; loads < MAX_CONSTANT; ++loads) {
                        program->args->mixers = mixers;
                        program->args->tables = tables;
                        program->args->fermentations = fermentation_cap;
                        program->args->ovens = ovens;
                        program->args->loads = loads;
                        program->reinit();
                        auto result = simulate(program);
                        results.push_back(result);
                    }
                }
            }
        }
        std::cout << mixers << "; ";
    }
    std::cout << std::endl;

    const auto min = *std::min_element(results.begin(), results.end()) / SECONDS_PER_MINUTE;
    const auto max = *std::max_element(results.begin(), results.end()) / SECONDS_PER_MINUTE;
    std::cout << "min: " << min << " minutes"
              << ", " << min / SECONDS_PER_MINUTE << " hours" << std::endl;
    std::cout << "max: " << max << " minutes"
              << ", " << max / SECONDS_PER_MINUTE << " hours" << std::endl;
}
