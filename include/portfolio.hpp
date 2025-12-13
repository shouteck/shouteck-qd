#pragma once

#include "execution.hpp"
#include <vector>

class Portfolio {
public:
    // C++ specific safety feature
    // prevents Portfolio p = 1000.0;
    explicit Portfolio(double initial_cash);

    // Apply an executed order
    void apply(const Order& order);

    double cash() const;
    int position() const;

    // Total value given current market price
    double equity(double market_price) const;

private:
    double cash_;
    int position_;
};
