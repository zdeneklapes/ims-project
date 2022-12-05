/**
 * IMS-PROJECT VUT FIT - Bakery
 *
 * @file experiments.cpp
 * @author Zdenek Lapes (xlapes02)
 * @author Andrej Binovsky (xbinov00)
 */

#include "experiments.h"

TestResult::TestResult(const size_t _mixers, const size_t _tables, const size_t _fermentations, const size_t _ovens,
                       const size_t _loads, const size_t _simulations, const size_t _breads,
                       const size_t _mixer_capacity, const size_t _cart_capacity, const size_t _simulation_time)
    : mixers(_mixers),
      tables(_tables),
      fermentations(_fermentations),
      ovens(_ovens),
      loads(_loads),
      breads(_breads),
      simulations(_simulations),
      mixer_capacity(_mixer_capacity),
      cart_capacity(_cart_capacity),
      simulation_time(_simulation_time) {}

TestResult::~TestResult() = default;

void print_test_result(std::vector<TestResult *> &results) {
    //
    const auto test_result_min = *std::min_element(
        results.begin(), results.end(),
        [](const TestResult *a, const TestResult *b) { return a->simulation_time < b->simulation_time; });
    const auto test_result_max = *std::max_element(
        results.begin(), results.end(),
        [](const TestResult *a, const TestResult *b) { return a->simulation_time < b->simulation_time; });

    auto print_info = [](std::string &msg, TestResult *result) {
        std::cout << msg << floor(result->simulation_time / SECONDS_PER_MINUTE) << ", breads: " << result->breads
                  << ", mixers: " << result->mixers << ", tables: " << result->tables
                  << ", fermentations: " << result->fermentations << ", ovens: " << result->ovens
                  << ", loads: " << result->loads << ", mixer_capacity: " << result->mixer_capacity
                  << ", cart_capacity: " << result->cart_capacity << std::endl;
        //        std::cout << floor(result->simulation_time / SECONDS_PER_MINUTE) << " & " << result->breads << " & "
        //                  << result->mixers << " & " << result->tables << " & " << result->fermentations << " & "
        //                  << result->ovens << " & " << result->loads << " & " << result->mixer_capacity << " & "
        //                  << result->cart_capacity << " \\\\ \\hline" << std::endl;
    };

    std::string msg_min = "Min time: ";
    std::string msg_max = "Max time: ";
    print_info(msg_min, test_result_min);
    print_info(msg_max, test_result_max);
    std::cout << std::endl;
}

void experiments(Program *program) {
    std::vector<TestResult *> results;

    const int breads_count = 4;
    const int breads_mul = 140;
    const int facilities_count = 10;

    //
    for (int breads = breads_mul; breads < breads_mul * breads_count; breads += breads_mul) {
        for (int mixers = 1; mixers < facilities_count; ++mixers) {
            for (int tables = 1; tables < facilities_count; ++tables) {
                for (int fermentation_cap = 1; fermentation_cap < facilities_count; ++fermentation_cap) {
                    for (int ovens = 1; ovens < facilities_count; ++ovens) {
                        for (int loads = 1; loads < facilities_count; ++loads) {
                            program->args->breads = breads;
                            program->args->mixers = mixers;
                            program->args->tables = tables;
                            program->args->fermentations = fermentation_cap;
                            program->args->ovens = ovens;
                            program->args->loads = loads;
                            program->reinit();
                            simulate(program);
                            results.push_back(new TestResult(program->args->mixers, program->args->tables,
                                                             program->args->fermentations, program->args->ovens,
                                                             program->args->loads, program->args->simulations,
                                                             program->args->breads, program->args->mixer_capacity,
                                                             program->args->cart_capacity, program->simulation_time));
                        }
                    }
                }
            }
        }
        print_test_result(results);
        results.clear();
    }
}
