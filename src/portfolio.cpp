#include "portfolio.hpp"

Portfolio::Portfolio(double initial_cash)
    : cash_(initial_cash),
      position_(0),
      initial_cash_(initial_cash) {}

void Portfolio::apply_fill(Signal signal, int quantity, double price) {
    if (signal == Signal::Buy) {
        cash_ -= quantity * price;
        position_ += quantity;
    } else if (signal == Signal::Sell) {
        cash_ += quantity * price;
        position_ -= quantity;
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

double Portfolio::pnl(double market_price) const {
    return equity(market_price) - initial_cash_;
}
