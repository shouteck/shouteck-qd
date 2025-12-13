#pragma once

#include "signal.hpp"

class Strategy {
public:
    Strategy() = default;

    Signal on_price(double price);

private:
    double last_price_ = 0.0;
    bool has_last_price_ = false;
};
