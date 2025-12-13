#include "portfolio.hpp"

// : is used here to initialize items that must be inside backpack
Portfolio::Portfolio(double initial_cash)
    : cash_(initial_cash), position_(0), realized_pnl_(0.0) {}

void Portfolio::apply(const Order& order) {
    if (order.signal == Signal::Buy) {
        cash_ -= order.execution_price;
        position_ += 1;
        open_lots_.push_back(order.execution_price);
    } else if (order.signal == Signal::Sell) {
        if (open_lots_.empty()) return; // safety
        double entry_price = open_lots_.front();
        open_lots_.pop_front();
        cash_ += order.execution_price;
        position_ -= 1;
        realized_pnl_ += order.execution_price - entry_price;
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
