#include "Program.h"

/******************************************************************************
 * Sources
 *****************************************************************************/
Sources::Sources(Args* _args) {
    mixers = std::vector<Facility>(_args->mixers);
    fermenting = new Store("Fermentation capacity", _args->fermentations);
    tables = std::vector<Facility>(_args->tables);
    ovens = std::vector<Facility>(_args->ovens);
    loading = new Store("Load capacity", 1);  // one cart per time
    orders = new Store("Order capacity", 1);  // flag for day order
}

Sources::~Sources() {
    delete fermenting;
    delete loading;
    delete orders;
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
