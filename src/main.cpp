#include <iostream>
#include <vector>

#include "strategy.hpp"
#include "execution.hpp"
#include "portfolio.hpp"
#include "signal.hpp"

int main() {
    // --- Risk control ---
    static constexpr double MAX_LOSS = 500.0; // dollars

    // --- System components ---
    Portfolio portfolio(10'000.0);
    Strategy strategy;
    ExecutionEngine execution;

    // --- Simulated market data (replace with live feed later) ---
    std::vector<double> prices = {
        100.0, 101.0, 102.5, 101.8, 103.0,
        104.2, 103.5, 105.0, 104.0
    };

    // --- Event-driven trading loop ---
    for (double price : prices) {
        // 1. Check kill switch BEFORE trading
        double current_pnl = portfolio.pnl(price);
        if (current_pnl <= -MAX_LOSS) {
            std::cout << "KILL SWITCH TRIGGERED\n";
            std::cout << "Final PnL: " << current_pnl << "\n";
            break;
        }

        // 2. Strategy decision
        Signal signal = strategy.on_price(price);

        // 3. Execute trade (may be rejected)
        execution.execute(signal, price, portfolio);

        // 4. Monitoring output
        std::cout
            << "Price: " << price
            << " | Cash: " << portfolio.cash()
            << " | Pos: " << portfolio.position()
            << " | Equity: " << portfolio.equity(price)
            << " | PnL: " << portfolio.pnl(price)
            << "\n";
    }

    return 0;
}
