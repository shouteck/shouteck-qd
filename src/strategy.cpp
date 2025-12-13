#include "strategy.hpp"

Strategy::Strategy() {}

void Strategy::on_day(
    int day,
    const std::vector<double>& prices,
    ExecutionEngine& execution
) {
    // Very simple demo strategy:
    // Buy on even days, sell on odd days

    Signal signal = (day % 2 == 0) ? Signal::Buy : Signal::Sell;

    TimedSignal timed_signal;
    timed_signal.execute_day = day + 1;  // enforce next-day execution
    timed_signal.signal = signal;

    execution.accept(timed_signal);
}
