#include "execution.hpp"
#include "portfolio.hpp"

bool ExecutionEngine::execute(
    Signal signal,
    double market_price,
    Portfolio& portfolio
) {
    if (signal == Signal::Hold) return false;

    static constexpr double RISK_FRACTION = 0.10;
    static constexpr double SLIPPAGE = 0.01;
    static constexpr double COMMISSION = 0.005;

    int quantity = static_cast<int>(
        (portfolio.cash() * RISK_FRACTION) / market_price
    );

    if (quantity <= 0) return false;

    double execution_price = market_price;

    if (signal == Signal::Buy) {
        execution_price += SLIPPAGE;
    } else if (signal == Signal::Sell) {
        execution_price -= SLIPPAGE;
    }
    
    double total_cost =
        quantity * execution_price +
        quantity * COMMISSION;
    
    if (signal == Signal::Buy && total_cost > portfolio.cash()) {
        return false;
    }    

    portfolio.apply_fill(signal, quantity, execution_price);
    return true;
}
