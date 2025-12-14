#include "portfolio.hpp"
#include "execution.hpp"

Portfolio::Portfolio(double initial_cash)
    : cash_(initial_cash),
      position_(0),
      initial_cash_(initial_cash) {}

void Portfolio::apply_fill(const PendingOrder& order, double price) {
    if (order.side == Signal::Buy) {
        cash_ -= price * order.quantity;
        position_ += order.quantity;
    } else if (order.side == Signal::Sell) {
        cash_ += price * order.quantity;
        position_ -= order.quantity;
    }
}

double Portfolio::cash() const { return cash_; }
int Portfolio::position() const { return position_; }
double Portfolio::initial_cash() const { return initial_cash_; }

double Portfolio::equity(double price) const {
    return cash_ + position_ * price;
}
