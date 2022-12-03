//
// Created by Zdeněk Lapeš on 29/11/2022.
//

#ifndef SRC_PROGRAM_H_
#define SRC_PROGRAM_H_

#include <iostream>
#include <string>
#include <vector>

#include "Args.h"

/******************************************************************************
 * Sources
 *****************************************************************************/
class Sources {
   public:
    explicit Sources(Args *_args);
    ~Sources();

    // Bread baking steps
    std::vector<Facility *> mixers;  // mixers available in bakery
    std::vector<Facility *> tables;  // tables available in bakery
    Store *fermenting;               // fermentation room capacity in bakery
    std::vector<Facility *> ovens;   // ovens available in bakery
    Store *loading;                  // loading is evaluated per cart which are waiting to be loaded in queue

    //
    Store *orders;  // flag if all breads are baked

    //
    Facility *get_facility_to_use(const std::vector<Facility *> &facilities);
    size_t get_free_facility_len(const std::vector<Facility *> &facilities);

    //
    bool all_sources_free() const;
};

/******************************************************************************
 * CustomStats
 *****************************************************************************/
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

/******************************************************************************
 * Program
 *****************************************************************************/
class Program {
   public:
    explicit Program(Args *_args, Sources *_stores);
    ~Program();

    //
    //    void print_data() const;
    void reinit();

    Args *args;
    Sources *sources;
    CustomStats *stats;
    double simulation_time = 0;
};

#endif  // SRC_PROGRAM_H_
