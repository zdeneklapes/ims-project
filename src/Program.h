/**
 * IMS-PROJECT VUT FIT - Bakery
 *
 * @file Program.h
 * @author Zdenek Lapes (xlapes02)
 * @author Andrej Binovsky (xbinov00)
 */

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
    /**
     * @brief Construct a new Sources object
     * @param _args Args*
     */
    explicit Sources(Args *_args);

    /**
     * @brief Destroy the Sources object
     */
    ~Sources();

    //////////////////////
    // Facilities & Stores
    //////////////////////
    std::vector<Facility *> mixers;  // mixers available in bakery
    std::vector<Facility *> tables;  // tables available in bakery
    Store *fermenting;               // fermentation room capacity in bakery
    std::vector<Facility *> ovens;   // ovens available in bakery
    Store *loading;                  // loading is evaluated per cart which are waiting to be loaded in queue
    Store *orders;                   // flag if all breads are baked

    //////////////////////
    // Methods
    //////////////////////
    Facility *get_facility_to_use(const std::vector<Facility *> &facilities);
    size_t get_free_facility_len(const std::vector<Facility *> &facilities);
    bool all_sources_free() const;
};

/******************************************************************************
 * CustomStats
 *****************************************************************************/
class CustomStats {
   public:
    /**
     * @brief Construct a new Custom Stats object
     */
    CustomStats();

    /**
     * @brief Destroy the Custom Stats object
     */
    ~CustomStats();

    //////////////////////
    // Stats
    //////////////////////
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
    /**
     * Constructor
     * @param _args Args*
     * @param _stores Sources*
     */
    explicit Program(Args *_args, Sources *_stores);

    /**
     * Copy constructor
     * @param p Program* - to copy
     */
    Program(const Program &);

    /**
     * Destructor
     */
    ~Program();

    //////////////////////
    // Methods
    //////////////////////
    /**
     * Print all data from CustomStats and Sources classes
     */
    void print_data() const;

    /**
     * Reinitialize all data from CustomStats and Sources classes
     */
    void reinit();

    //////////////////////
    // Fields
    //////////////////////
    Args *args;
    Sources *sources;
    CustomStats *stats;

    //////////////////////
    // Members
    //////////////////////
    double simulation_time = 0;
};

#endif  // SRC_PROGRAM_H_
