bool ExecutionEngine::execute(
    int day,
    double market_price,
    Portfolio& portfolio,
    Order& out_order
) {
    if (!has_pending_signal_) return false;
    if (pending_signal_.execute_day != day) return false;

    static constexpr double RISK_FRACTION = 0.10;
    static constexpr double SLIPPAGE = 0.01;        // $0.01 per share
    static constexpr double COMMISSION = 0.005;     // $0.005 per share

    int quantity = static_cast<int>(
        (portfolio.cash() * RISK_FRACTION) / market_price
    );

    if (quantity <= 0) return false;

    double execution_price = market_price;

    if (pending_signal_.signal == Signal::Buy) {
        execution_price += SLIPPAGE;
    } else if (pending_signal_.signal == Signal::Sell) {
        execution_price -= SLIPPAGE;
    }

    out_order.signal = pending_signal_.signal;
    out_order.quantity = quantity;
    out_order.execution_price = execution_price;

    // Commission is applied implicitly via cash in Portfolio
    out_order.execution_price += COMMISSION;

    has_pending_signal_ = false;
    return true;
}
