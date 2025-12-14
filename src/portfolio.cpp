#include "portfolio.hpp"

Portfolio::Portfolio(double initial_cash)
    : cash_(initial_cash),
      position_(0),
      initial_cash_(initial_cash) {}

double Portfolio::cash() const {
    return cash_;
}

int Portfolio::position() const {
    return position_;
}

double Portfolio::equity(double price) const {
    return cash_ + position_ * price;
}

double Portfolio::pnl(double price) const {
    return equity(price) - initial_cash_;
}

int Portfolio::max_affordable_quantity() const {
    return static_cast<int>(cash_ / 100.0); // assumes ~$100 stock
}

void Portfolio::buy(int quantity, double price) {
    cash_ -= quantity * price;
    position_ += quantity;
}

void Portfolio::sell(int quantity, double price) {
    cash_ += quantity * price;
    position_ -= quantity;
}
