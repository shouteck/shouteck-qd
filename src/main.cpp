#include <iostream>
#include <vector>
#include <string>

#include "strategy.hpp"
#include "execution.hpp"
#include "portfolio.hpp"
#include "signal.hpp"

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
    // Market data (placeholder)
    // -----------------------------
    std::vector<double> prices = {
        100.0, 101.0, 102.5, 101.8,
        103.0, 104.2, 103.5, 105.0,
        104.0
    };

    // -----------------------------
    // Event-driven trading loop
    // -----------------------------
    for (double price : prices) {
        // 1. Kill switch (hard risk stop)
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
            << " Price=" << price
            << " Cash=" << portfolio.cash()
            << " Pos=" << portfolio.position()
            << " Equity=" << portfolio.equity(price)
            << " PnL=" << portfolio.pnl(price)
            << "\n";
    }

    return 0;
}
