#include "execution.hpp"

void ExecutionEngine::submit(Signal signal) {
    if (signal == Signal::Hold) {
        return;
    }
    has_pending_signal_ = true;
    pending_signal_ = signal;
}

bool ExecutionEngine::execute(
    const std::string& date,
    double open_price,
    Order& out_order
) {
    if (!has_pending_signal_) {
        return false;
    }

    out_order.signal = pending_signal_;
    out_order.execution_date = date;
    out_order.execution_price = open_price;

    has_pending_signal_ = false;
    return true;
}

bool ExecutionEngine::has_pending() const {
    return has_pending_signal_;
}
