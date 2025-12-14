#include <iostream>
#include <string>

#include "strategy.hpp"
#include "execution.hpp"
#include "portfolio.hpp"
#include "signal.hpp"
#include "market_data.hpp"

std::string to_string(Signal signal) {
    switch (signal) {
        case Signal::Buy:  return "BUY";
        case Signal::Sell: return "SELL";
        case Signal::Hold: return "HOLD";
    }
    return "UNKNOWN";
}

int main() {
    static constexpr double MAX_LOSS = 500.0;

    Portfolio portfolio(10'000.0);
    Strategy strategy;
    ExecutionEngine execution;

    auto market_data = load_market_data("data/AAPL.csv");

    for (const MarketTick& tick : market_data) {
        double price = tick.price;

        // 1. Fill pending orders
        execution.on_tick(price, portfolio);

        // 2. Kill switch
        double current_pnl = portfolio.pnl(price);
        if (current_pnl <= -MAX_LOSS) {
            std::cout << "[KILL] Max loss reached. PnL="
                      << current_pnl << "\n";
            break;
        }

        // 3. Strategy decision
        Signal signal = strategy.on_price(price);

        // 4. Submit order
        execution.submit(signal, price, portfolio);

        // 5. State logging
        std::cout
            << "[STATE]"
            << " Time=" << tick.timestamp
            << " Price=" << price
            << " Cash=" << portfolio.cash()
            << " Pos=" << portfolio.position()
            << " Equity=" << portfolio.equity(price)
            << " PnL=" << portfolio.pnl(price)
            << "\n";
    }

    return 0;
}
