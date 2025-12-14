#pragma once

#include "signal.hpp"

struct PendingOrder {
    Signal side;
    int quantity;
};

class ExecutionEngine {
public:
    explicit ExecutionEngine(double risk_fraction);

    void submit_signal(Signal signal);
    void on_tick();

    bool has_pending_order() const;
    bool has_filled_order() const;

    const PendingOrder& filled_order() const;
    void clear_filled_order();

private:
    double risk_fraction_;

    bool has_pending_;
    bool has_filled_;

    PendingOrder pending_order_;
    PendingOrder filled_order_;
};
