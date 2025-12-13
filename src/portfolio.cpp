#include "portfolio.hpp"

Portfolio::Portfolio(double initial_cash)
    : cash_(initial_cash),
      position_(0),
      realized_pnl_(0.0) {}

void Portfolio::apply(const Order& order) {
    if (order.signal == Signal::Buy) {
        cash_ -= order.execution_price * order.quantity;
        position_ += order.quantity;

        for (int i = 0; i < order.quantity; ++i) {
            open_lots_.push_back(order.execution_price);
        }
    }
    else if (order.signal == Signal::Sell) {
        for (int i = 0; i < order.quantity; ++i) {
            if (open_lots_.empty()) break;

            double entry_price = open_lots_.front();
            open_lots_.pop_front();

            realized_pnl_ += (order.execution_price - entry_price);
            cash_ += order.execution_price;
            position_ -= 1;
        }
    }
}

double Portfolio::cash() const {
    return cash_;
}

int Portfolio::position() const {
    return position_;
}

double Portfolio::equity(double market_price) const {
    return cash_ + position_ * market_price;
}

double Portfolio::realized_pnl() const {
    return realized_pnl_;
}
