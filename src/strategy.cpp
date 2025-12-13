#include "strategy.hpp"

Strategy::Strategy()
    : has_position_(false) {}

void Strategy::on_day(
    int time_index,
    const std::vector<double>& prices,
    ExecutionEngine& execution
) {
    // Need at least 2 days to compare
    if (time_index == 0) {
        return;
    }

    double today = prices[time_index];
    double yesterday = prices[time_index - 1];

    // Simple rule:
    // If price goes up and we don't have a position → Buy
    if (!has_position_ && today > yesterday) {
        execution.submit(Signal::Buy, time_index);
        has_position_ = true;
    }

    // If price goes down and we have a position → Sell
    else if (has_position_ && today < yesterday) {
        execution.submit(Signal::Sell, time_index);
        has_position_ = false;
    }
}
