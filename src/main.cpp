#include "market_data.hpp"
#include "strategy.hpp"
#include "execution.hpp"
#include "portfolio.hpp"
#include "logger.hpp"

int main() {
    MarketData market_data("data/AAPL.csv");

    Strategy strategy;
    ExecutionEngine execution(0.1);
    Portfolio portfolio(100000.0);
    Logger logger("logs/run.csv");

    while (market_data.has_next()) {
        MarketTick tick = market_data.next();

        // Fill t-1 orders
        execution.on_tick();

        if (execution.has_filled_order()) {
            portfolio.apply_fill(execution.filled_order(), tick.price);
            execution.clear_filled_order();
        }

        // Generate signal at t
        Signal signal = strategy.on_tick(tick.price);
        execution.submit_signal(signal);

        // Log everything
        logger.log_tick(tick, portfolio, execution);
    }

    return 0;
}
