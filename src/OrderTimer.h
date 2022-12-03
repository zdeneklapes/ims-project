#ifndef SRC_ORDERTIMER_H_
#define SRC_ORDERTIMER_H_

//
#include <simlib.h>

//
class OrderProcess;
#include "Processes.h"

//
class OrderTimer : public simlib3::Event {
   public:
    explicit OrderTimer(OrderProcess* _order_process);
    ~OrderTimer() override;
    void Behavior() override;

    //
    constexpr static const double ORDER_WORK_TIME_START_SEC = 0;
    constexpr static const double ORDER_WORK_TIME_END_SEC = 8 * 60 * SECONDS_PER_MINUTE;  // 8 hours: work time

   private:
    OrderProcess* order_process;
};
#endif  // SRC_ORDERTIMER_H_
