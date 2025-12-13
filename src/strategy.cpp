#include "strategy.hpp"

Signal Strategy::on_price(double price) {
    if (!has_last_price_) {
        last_price_ = price;
        has_last_price_ = true;
        return Signal::Hold;
    }

    Signal signal = Signal::Hold;

    if (price > last_price_) {
        signal = Signal::Buy;
    } else if (price < last_price_) {
        signal = Signal::Sell;
    }

    last_price_ = price;
    return signal;
}
