#pragma once

#include <optional>

#include "signal.hpp"
#include "order.hpp"

class Portfolio;

class ExecutionEngine {
public:
    ExecutionEngine();

    void submit(Signal signal, double price, Portfolio& portfolio);
    void on_tick(double price, Portfolio& portfolio);

private:
    std::optional<PendingOrder> pending_order_;
};
