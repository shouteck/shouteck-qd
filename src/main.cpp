#include <iostream>
#include <vector>

#include "strategy.hpp"
#include "execution.hpp"
#include "portfolio.hpp"

int main() {
    std::vector<double> prices = {
        100.0, 102.0, 101.0, 105.0, 103.0
    };

    Strategy strategy;
    ExecutionEngine execution;
    Portfolio portfolio(1000.0);

    double prev_equity = portfolio.equity(prices[0]);

    for (int day = 0; day < prices.size(); ++day) {
        double price = prices[day];

        // Strategy generates signals
        strategy.on_day(day, prices, execution);

        // Execution processes eligible signals
        Order order;
        if (execution.execute(day, price, portfolio, order)) {
            portfolio.apply(order);
        }

        // Performance tracking
        double equity = portfolio.equity(price);
        double pnl = equity - prev_equity;
        double ret = pnl / prev_equity;

        std::cout << "Day " << day
                  << " | Equity: " << equity
                  << " | PnL: " << pnl
                  << " | Return: " << ret
                  << "\n";

        prev_equity = equity;
    }

    return 0;
}
