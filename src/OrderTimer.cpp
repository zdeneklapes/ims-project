#include "OrderTimer.h"

/******************************************************************************
 * OrderProcess
 *****************************************************************************/
OrderTimer::OrderTimer(OrderProcess* _order_process) : order_process(_order_process) {
    Activate(Time + ORDER_WORK_TIME_END_SEC);
}

OrderTimer::~OrderTimer() = default;

void OrderTimer::Behavior() {
    //
    delete order_process;
}
