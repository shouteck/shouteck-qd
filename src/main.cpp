#include <iostream>
#include <string>

#include "strategy.hpp"
#include "execution.hpp"
#include "portfolio.hpp"
#include "signal.hpp"
#include "market_data.hpp"

// Helper for readable logs
std::string to_string(Signal signal) {
    switch (signal) {
        case Signal::Buy:  return "BUY";
        case Signal::Sell: return "SELL";
        case Signal::Hold: return "HOLD";
    }
    return "UNKNOWN";
}

int main() {
    // -----------------------------
    // Risk configuration
    // -----------------------------
    static constexpr double MAX_LOSS = 500.0;

    // -----------------------------
    // Core system components
    // -----------------------------
    Portfolio portfolio(10'000.0);
    Strategy strategy;
    ExecutionEngine execution;

    // -----------------------------
    // Load market data (US hours only)
    // -----------------------------
    auto market_data = load_market_data("data/AAPL.csv");

    // -----------------------------
    // Event-driven trading loop
    // -----------------------------
    for (const MarketTick& tick : market_data) {
        double price = tick.price;

        // 1. Kill switch
        double current_pnl = portfolio.pnl(price);
        if (current_pnl <= -MAX_LOSS) {
            std::cout << "[KILL] Max loss reached. PnL="
                      << current_pnl << "\n";
            break;
        }

        // 2. Strategy decision
        Signal signal = strategy.on_price(price);

        // 3. Attempt execution
        bool executed = execution.execute(signal, price, portfolio);

        // 4. Trade logging
        if (signal != Signal::Hold) {
            if (executed) {
                std::cout << "[TRADE] "
                          << to_string(signal)
                          << " @ " << price << "\n";
            } else {
                std::cout << "[REJECT] "
                          << to_string(signal)
                          << " @ " << price << "\n";
            }
        }

        // 5. State snapshot
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
