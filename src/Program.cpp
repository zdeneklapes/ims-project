#include "Program.h"

/******************************************************************************
 * Sources
 *****************************************************************************/
Sources::Sources(Args* _args) {
    for (size_t i = 0; i < _args->mixers; ++i) {
        mixers.push_back(new Facility("mixer"));
    }
    for (size_t i = 0; i < _args->tables; ++i) {
        tables.push_back(new Facility("table"));
    }
    fermenting = new Store("Fermentation capacity", _args->fermentations);
    for (size_t i = 0; i < _args->ovens; ++i) {
        ovens.push_back(new Facility("oven"));
    }
    loading = new Store("Load capacity", _args->loads);  // one cart per time

    //
    orders = new Store("Order capacity", 1);  // flag for day order
}

Sources::~Sources() {
    //
    delete fermenting;
    delete loading;
    delete orders;
}

Facility* Sources::get_facility_to_use(const std::vector<Facility*>& facilities) {
    for (auto facility : facilities) {
        if (!facility->Busy()) {
            return facility;
        }
    }
    return facilities[0];
}

size_t Sources::get_free_facility_len(const std::vector<Facility*>& facilities) {
    size_t free_facilities = 0;
    for (auto facility : facilities) {
        if (!facility->Busy()) {
            free_facilities++;
        }
    }
    return free_facilities;
}
bool Sources::all_sources_free() const {
    bool are_mixers_free = std::all_of(mixers.cbegin(), mixers.cend(), [](Facility* f) { return !f->Busy(); });
    bool are_tables_free = std::all_of(tables.cbegin(), tables.cend(), [](Facility* f) { return !f->Busy(); });
    bool are_ovens_free = std::all_of(ovens.cbegin(), ovens.cend(), [](Facility* f) { return !f->Busy(); });
    bool is_loading_free = loading->Empty();
    bool is_fermenting_free = fermenting->Empty();
    return (are_mixers_free && are_tables_free && are_ovens_free && is_loading_free && is_fermenting_free);
}

/******************************************************************************
 * CustomStats
 *****************************************************************************/
CustomStats::CustomStats()
    : mix_duration(new Stat("Mix duration")),
      cut_duration(new Stat("Cut duration")),
      fermentation_duration(new Stat("Fermentation duration")),
      bake_duration(new Stat("Bake duration")),
      load_duration(new Stat("Load duration")) {}

CustomStats::~CustomStats() {
    //
    delete mix_duration;
    delete cut_duration;
    delete fermentation_duration;
    delete bake_duration;
    delete load_duration;
}

/******************************************************************************
 * Program
 *****************************************************************************/
Program::Program(Args* _args, Sources* _stores) : args(_args), sources(_stores), stats(new CustomStats()) {}

Program::Program(const Program& p) {
    args = new Args(*p.args);
    sources = p.sources;
    stats = p.stats;
    simulation_time = p.simulation_time;
}

Program::~Program() {
    delete args;
    delete sources;
    delete stats;
}
void Program::reinit() {
    //
    delete stats;
    delete sources;

    //
    stats = new CustomStats();
    sources = new Sources(args);
}

void Program::print_data() const {
    // STATS
    Print("\n=================== STATS ====================\n");
    stats->mix_duration->Output();
    stats->cut_duration->Output();
    stats->fermentation_duration->Output();
    stats->bake_duration->Output();
    stats->load_duration->Output();

    // SOURCES
    Print("\n=================== STORES / FACILITIES ====================\n");
    for (const auto& f : sources->mixers) f->Output();
    for (const auto& f : sources->tables) f->Output();
    sources->fermenting->Output();
    for (const auto& f : sources->ovens) f->Output();
    sources->loading->Output();
    sources->orders->Output();

    // ALL
    const auto total_bake_time =
        (stats->mix_duration->Sum() + stats->cut_duration->Sum() + stats->fermentation_duration->Sum() +
         stats->bake_duration->Sum() + stats->load_duration->Sum()) /
        SECONDS_PER_MINUTE;
    const auto mean_bake_time_minutes = (stats->mix_duration->MeanValue() + stats->cut_duration->MeanValue() +
                                         stats->fermentation_duration->MeanValue() + stats->bake_duration->MeanValue() +
                                         stats->load_duration->MeanValue()) /
                                        SECONDS_PER_MINUTE;
    Print("=================== ALL ====================\n");
    Print("Total bake time (%d loaves of bread): %d minutes (%f hours)\n", (int)args->breads,
          (int)(simulation_time / SECONDS_PER_MINUTE), (simulation_time / SECONDS_PER_MINUTE / SECONDS_PER_MINUTE));
    Print("Machines Run time: %d minutes (%f hours)\n", (int)total_bake_time, (total_bake_time / SECONDS_PER_MINUTE));
    Print("Mean time to bake 1 bread: %d minutes (%f hours)\n", (int)mean_bake_time_minutes,
          (mean_bake_time_minutes / SECONDS_PER_MINUTE));
}
