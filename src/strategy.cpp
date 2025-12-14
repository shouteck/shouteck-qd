#include "strategy.hpp"

Strategy::Strategy()
    : last_price_(0.0) {}

Signal Strategy::on_price(double price) const {
    if (last_price_ == 0.0) {
        last_price_ = price;
        return Signal::Hold;
    }

    if (price > last_price_) {
        last_price_ = price;
        return Signal::Buy;
    }

    if (price < last_price_) {
        last_price_ = price;
        return Signal::Sell;
    }

    return Signal::Hold;
}
