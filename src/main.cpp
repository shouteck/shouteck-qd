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
    Strategy strategy;

    // 3. Simulate days
    double pre_equity = portfolio.equity(prices[0]);
    for (int day = 0; day < prices.size(); ++day) {
        double today_price = prices[day];

        // --- Strategy observes today ---
        strategy.on_day(day, prices, execution);

        // --- Execution executes older signals ---
        Order order;
        if (execution.execute(day, today_price, order)) {
            portfolio.apply(order);
        }

        // --- Portfolio state ---
        double equity = portfolio.equity(today_price);
        double daily_pnl = equity - pre_equity;
        double daily_return = daily_pnl / pre_equity;

        std::cout << " Day: " << day
                  << " | Equity: " << equity
                  << " | PnL: " << daily_pnl
                  << " | Return: " << daily_return
                  << "\n";

        pre_equity = equity;
    }

    return 0;
}
