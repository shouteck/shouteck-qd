#include "portfolio.hpp"

// : is used here to initialize items that must be inside backpack
Portfolio::Portfolio(double initial_cash)
    : cash_(initial_cash), position_(0) {}

void Portfolio::apply(const Order& order) {
    if (order.signal == Signal::Buy) {
        cash_ -= order.execution_price;
        position_ += 1;
    } else if (order.signal == Signal::Sell) {
        cash_ += order.execution_price;
        position_ -= 1;
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
