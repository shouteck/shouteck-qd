#include "strategy.hpp"

Strategy::Strategy() {}

Signal Strategy::on_tick(double price) {
    if (price < 100.0) {
        return Signal::Buy;
    }
    if (price > 110.0) {
        return Signal::Sell;
    }
    return Signal::Hold;
}
