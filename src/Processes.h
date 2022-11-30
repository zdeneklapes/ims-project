#ifndef SRC_PROCESSES_H_
#define SRC_PROCESSES_H_

#include "simlib.h"

class WorkShiftProcess : public Process {
   public:  // NOLINT
    WorkShiftProcess() = default;
    ~WorkShiftProcess() override = default;

    void Behavior() override;
};

class FermentationProcess : public Process {
   public:  // NOLINT
    FermentationProcess() = default;
    ~FermentationProcess() override = default;
    void Behavior() override;

   private:  // NOLINT
    Stat *fermentation_duration;
};

class BakeProcess : public Process {
   public:  // NOLINT
    BakeProcess() = default;
    ~BakeProcess() override = default;
    void Behavior() override;

   private:  // NOLINT
    Stat *bake_duration;
};

class MixProcess : public Process {
   public:  // NOLINT
    MixProcess() = default;
    ~MixProcess() override = default;
    void Behavior() override;

   private:  // NOLINT
    Stat *mix_duration;
};

#endif  // SRC_PROCESSES_H_
