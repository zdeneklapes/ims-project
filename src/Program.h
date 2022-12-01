//
// Created by Zdeněk Lapeš on 29/11/2022.
//

#ifndef SRC_PROGRAM_H_
#define SRC_PROGRAM_H_
#include "Args.h"

class CustomStores {
   public:
    explicit CustomStores(Args *_args);
    ~CustomStores();

    Store *mixing;
    Store *cutting;
    Store *fermenting;
    Store *baking;
    Store *loading;
};

class CustomStats {
   public:
    CustomStats();
    ~CustomStats();

    //
    Stat *mix_duration;
    Stat *cut_duration;
    Stat *fermentation_duration;
    Stat *bake_duration;
    Stat *load_duration;
};

class Program {
   public:
    explicit Program(Args *_args, CustomStores *_stores);
    ~Program();

    Args *args;
    CustomStores *stores;
    CustomStats *stats;
    bool is_running = true;
};

#endif  // SRC_PROGRAM_H_
