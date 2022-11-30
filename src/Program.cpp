#include "Program.h"

Program::Program(Args* _args, CustomStores* _stores) : args(_args), stores(_stores) {}
Program::~Program() {
    delete args;
    delete stores;
}

CustomStores::CustomStores(Args* _args) {
    // TODO: Capacity
    mixer_capacity = new Store("Mixer capacity", 1);  // default (1 mixer available)
    cut_capacity = new Store("Cutting capacity", 1);  // default (only 1 person can make loaves of bread)
    fermentation_capacity = new Store("Fermentation capacity", 1 * 8);  // default (1 fermentation room * 8 carts)
    bake_capacity = new Store("Bake capacity", 1 * 8);                  // default (1 oven * 8 carts)
    load_capacity = new Store("Bake capacity", 1 * 8);                  // default (1 oven * 8 carts)
}
CustomStores::~CustomStores() {
    delete &mixer_capacity;
    delete &cut_capacity;
    delete &fermentation_capacity;
    delete &bake_capacity;
    delete &load_capacity;
}
