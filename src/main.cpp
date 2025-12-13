#include "execution.hpp"
#include "portfolio.hpp"

#include <iostream>
#include <vector>

int main() {
    // 1. Fake market data (daily open prices)
    std::vector<double> prices = {
        100.0,
        102.0,
        101.0,
        105.0
    };

    // 2. Create core components
    ExecutionEngine execution;
    Portfolio portfolio(1000.0);

    // 3. Simulate days
    for (size_t day = 0; day < prices.size(); ++day) {
        double today_price = prices[day];

        std::cout << "Day " << day
                  << " | Price: " << today_price << "\n";

        // --- Strategy (hardcoded for now) ---
        if (day == 0) {
            execution.submit(Signal::Buy);
        }
        if (day == 2) {
            execution.submit(Signal::Sell);
        }

        // --- Execute trades from previous day ---
        Order order;
        if (execution.execute(today_price, order)) {
            portfolio.apply(order);
            std::cout << "  Executed order at "
                      << order.execution_price << "\n";
        }

        // --- Portfolio state ---
        std::cout << "  Cash: " << portfolio.cash()
                  << " | Position: " << portfolio.position()
                  << " | Equity: " << portfolio.equity(today_price)
                  << "\n\n";
    }

    return 0;
}
