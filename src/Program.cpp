#include "Program.h"

/******************************************************************************
 * Sources
 *****************************************************************************/
Sources::Sources(Args* _args) {
    mixers = std::vector<Facility*>(_args->mixers, new Facility("Mixer"));
    tables = std::vector<Facility*>(_args->tables, new Facility("Table"));
    fermenting = new Store("Fermentation capacity", _args->fermentations);
    ovens = std::vector<Facility*>(_args->ovens, new Facility("Oven"));
    loading = new Store("Load capacity", 1);  // one cart per time

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
