#include "Program.h"

/******************************************************************************
 * Sources
 *****************************************************************************/
Sources::Sources(Args* _args) {
    mixers = std::vector<Facility*>(_args->mixers, new Facility("Mixer"));
    tables = std::vector<Facility*>(_args->tables, new Facility("Table"));
    fermenting = new Store("Fermentation capacity", _args->fermentations);
    ovens = std::vector<Facility*>(_args->ovens, new Facility("Oven"));
    loading = new Store("Load capacity", _args->loads);  // one cart per time

    //
    orders = new Store("Order capacity", 1);  // flag for day order
}

Sources::~Sources() {
    delete fermenting;
    delete loading;
    delete orders;
}

Facility* Sources::get_facility_to_use(const std::vector<Facility*> facilities) {
    for (auto facility : facilities) {
        if (!facility->Busy()) {
            return *facility;
        }
    }
    return facilities[0];
}

size_t Sources::get_free_facility_len(const std::vector<Facility*> facilities) {
    size_t free_facilities = 0;
    for (auto facility : facilities) {
        if (!facility->Busy()) {
            free_facilities++;
        }
    }
    return free_facilities;
}
bool Sources::all_sources_free() {
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

Program::~Program() {
    delete args;
    delete sources;
    delete stats;
}
