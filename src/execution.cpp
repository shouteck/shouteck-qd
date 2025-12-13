#include "execution.hpp"
#include "portfolio.hpp"

void ExecutionEngine::accept(const TimedSignal& signal) {
    pending_signal_ = signal;
    has_pending_signal_ = true;
}

bool ExecutionEngine::execute(
    int day,
    double market_price,
    Portfolio& portfolio,
    Order& out_order
) {
    if (!has_pending_signal_) return false;
    if (pending_signal_.execute_day != day) return false;

    // Static - belongs to the function, not the object
    // Constexpr - known at compile time
    // Willing to risk X% of cash
    static constexpr double RISK_FRACTION = 0.10;

    // I know this is a double but I intentionally want an integer, I accept truncation
    int quantity = static_cast<int>(
        (portfolio.cash() * RISK_FRACTION) / market_price
    );

    //  Not enough capital to trade safely
    if (quantity <= 0) return false;

    out_order.signal = pending_signal_.signal;
    out_order.quantity = quantity;
    out_order.execution_price = market_price;

    has_pending_signal_ = false;
    return true;
}
