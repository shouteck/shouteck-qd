#include "execution.hpp"
#include "portfolio.hpp"

ExecutionEngine::ExecutionEngine()
    : pending_order_(std::nullopt) {}

void ExecutionEngine::submit(Signal signal,
                             double /*price*/,
                             Portfolio& portfolio) {
    if (pending_order_.has_value()) {
        return;
    }

    if (signal == Signal::Hold) {
        return;
    }

    int quantity = portfolio.max_affordable_quantity();

    if (quantity <= 0) {
        return;
    }

    pending_order_ = PendingOrder{signal, quantity};
}

void ExecutionEngine::on_tick(double price, Portfolio& portfolio) {
    if (!pending_order_) {
        return;
    }

    const PendingOrder& order = *pending_order_;

    if (order.side == Signal::Buy) {
        portfolio.buy(order.quantity, price);
    } else if (order.side == Signal::Sell) {
        portfolio.sell(order.quantity, price);
    }

    pending_order_.reset();
}
