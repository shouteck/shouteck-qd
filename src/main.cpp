#include <iostream>
#include <vector>

#include "strategy.hpp"
#include "execution.hpp"
#include "portfolio.hpp"
#include "signal.hpp"

int main() {
    // 1. Initial setup
    Portfolio portfolio(10'000.0);
    Strategy strategy;
    ExecutionEngine execution;

    // 2. Simulated price stream (replace with live feed later)
    std::vector<double> prices = {
        100.0, 101.0, 102.5, 101.8, 103.0,
        104.2, 103.5, 105.0, 104.0
    };

    // 3. Event loop
    for (size_t i = 0; i < prices.size(); ++i) {
        double price = prices[i];

        Signal signal = strategy.on_price(price);

        execution.execute(signal, price, portfolio);

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
