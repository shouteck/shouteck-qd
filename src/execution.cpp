#include "execution.hpp"

ExecutionEngine::ExecutionEngine(double risk_fraction)
    : risk_fraction_(risk_fraction),
      has_pending_(false),
      has_filled_(false) {}

void ExecutionEngine::submit_signal(Signal signal) {
    if (signal == Signal::Hold || has_pending_) {
        return;
    }

    pending_order_ = { signal, 10 };
    has_pending_ = true;
}

void ExecutionEngine::on_tick() {
    if (has_pending_) {
        filled_order_ = pending_order_;
        has_pending_ = false;
        has_filled_ = true;
    }
}

bool ExecutionEngine::has_pending_order() const {
    return has_pending_;
}

bool ExecutionEngine::has_filled_order() const {
    return has_filled_;
}

const PendingOrder& ExecutionEngine::filled_order() const {
    return filled_order_;
}

void ExecutionEngine::clear_filled_order() {
    has_filled_ = false;
}
