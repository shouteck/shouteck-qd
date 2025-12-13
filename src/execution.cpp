#include "execution.hpp"

ExecutionEngine::ExecutionEngine()
    : has_pending_signal_(false) {}

void ExecutionEngine::submit(Signal signal, int time_index) {
    has_pending_signal_ = { signal, time_index };
    pending_signal_ = true;
}

bool ExecutionEngine::execute(
    int current_time,
    double open_price,
    Order& out_order
) {
    if (!has_pending_signal_) {
        return false;
    }

    if (current_time <= pending_signal_.time_index) {
        return false;
    }

    out_order.signal = pending_signal_.signal;
    out_order.execution_price = market_price;

    has_pending_signal_ = false;
    return true;
}

bool ExecutionEngine::has_pending() const {
    return has_pending_signal_;
}
