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

    Store *mixer_capacity;
    Store *cut_capacity;
    Store *fermentation_capacity;
    Store *bake_capacity;
    Store *load_capacity;
};

class Program {
   public:
    explicit Program(Args *_args, CustomStores *_stores);
    ~Program();

    Args *args;
    CustomStores *stores;
};

#endif  // SRC_PROGRAM_H_
