#include "Program.h"

/******************************************************************************
 * CustomStores
 *****************************************************************************/
CustomStores::CustomStores(Args* _args) {
    // TODO: Capacity
    mixing = new Store("Mixer capacity", _args->mixers);
    cutting = new Store("Cutting capacity", _args->tables * _args->table_capacity);
    fermenting = new Store("Fermentation capacity", _args->fermentations);  // default (1 fermentation room * 8 carts)
    baking = new Store("Bake capacity", _args->ovens);                      // default (1 oven * 8 carts)
    loading = new Store("Load capacity", 1);                                // default (1 oven * 8 carts)
}

CustomStores::~CustomStores() {
    delete mixing;
    delete cutting;
    delete fermenting;
    delete baking;
    delete loading;
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
Program::Program(Args* _args, CustomStores* _stores) : args(_args), stores(_stores), stats(new CustomStats()) {}

Program::~Program() {
    delete args;
    delete stores;
}
