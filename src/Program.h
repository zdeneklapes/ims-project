//
// Created by Zdeněk Lapeš on 29/11/2022.
//

#ifndef SRC_PROGRAM_H_
#define SRC_PROGRAM_H_

#include <iostream>
#include <vector>

#include "Args.h"

class Sources {
   public:
    explicit Sources(Args *_args);
    ~Sources();

    std::vector<Facility> mixers;  // mixers available in bakery
    std::vector<Facility> tables;  // tables available in bakery
    Store *fermenting;             // fermentation room capacity in bakery
    std::vector<Facility> ovens;   // ovens available in bakery
    Store *loading;                // loading is evaluated per cart which are waiting to be loaded in queue
    Store *orders;                 // flag if all breads are baked
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
    explicit Program(Args *_args, Sources *_stores);
    ~Program();

    Args *args;
    Sources *sources;
    CustomStats *stats;
    bool is_running = true;
};

#endif  // SRC_PROGRAM_H_
