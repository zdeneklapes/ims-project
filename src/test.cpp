#include "test.h"

class TestResult {
   public:
    TestResult(const size_t _mixers, const size_t _tables, const size_t _fermentations, const size_t _ovens,
               const size_t _loads, const size_t _simulations, const size_t _breads, const size_t _mixer_capacity,
               const size_t _cart_capacity, const size_t _simulation_time)
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
    ~TestResult() {}
    const size_t mixers;
    const size_t tables;
    const size_t fermentations;
    const size_t ovens;
    const size_t loads;
    const size_t breads;
    const size_t simulations;
    const size_t mixer_capacity;
    const size_t cart_capacity;
    const double simulation_time;
};

void print_test_result(std::vector<TestResult *> &results) {
    //
    const auto test_result_min = *std::min_element(
        results.begin(), results.end(),
        [](const TestResult *a, const TestResult *b) { return a->simulation_time < b->simulation_time; });
    const auto test_result_max = *std::max_element(
        results.begin(), results.end(),
        [](const TestResult *a, const TestResult *b) { return a->simulation_time < b->simulation_time; });

    auto print_info = [](std::string &msg, TestResult *result) {
        std::cout << msg << result->simulation_time << ", breads: " << result->breads << ", mixers: " << result->mixers
                  << ", tables: " << result->tables << ", fermentations: " << result->fermentations
                  << ", ovens: " << result->ovens << ", loads: " << result->loads
                  << ", simulations: " << result->simulations << ", mixer_capacity: " << result->mixer_capacity
                  << ", cart_capacity: " << result->cart_capacity << std::endl;
    };

    std::string msg_min = "Min time: ";
    std::string msg_max = "Max time: ";
    print_info(msg_min, test_result_min);
    print_info(msg_max, test_result_max);
    std::cout << std::endl;
}

void test1(Program *program) {
    std::vector<TestResult *> results;

    //
    for (int breads = 1; breads < 4; ++breads) {
        for (int mixers = 1; mixers < MAX_CONSTANT; ++mixers) {
            for (int tables = 1; tables < MAX_CONSTANT; ++tables) {
                for (int fermentation_cap = 1; fermentation_cap < MAX_CONSTANT; ++fermentation_cap) {
                    for (int ovens = 1; ovens < MAX_CONSTANT; ++ovens) {
                        for (int loads = 1; loads < MAX_CONSTANT; ++loads) {
                            program->args->breads = 100 * breads;
                            program->args->mixers = mixers;
                            program->args->tables = tables;
                            program->args->fermentations = fermentation_cap;
                            program->args->ovens = ovens;
                            program->args->loads = loads;
                            program->reinit();
                            simulate(program);
                            results.push_back(new TestResult(mixers, tables, fermentation_cap, ovens, loads,
                                                             program->args->simulations, program->args->breads,
                                                             program->args->mixer_capacity,
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
