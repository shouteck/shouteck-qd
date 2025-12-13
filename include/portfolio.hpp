#pragma once

#include "execution.hpp"

class Portfolio {
public:
    // C++ specific safety feature
    // prevents Portfolio p = 1000.0;
    explicit Portfolio(double initial_cash);

    // Apply an executed order
    void apply(const Order& order);

    // const means the method does not modify the object
    double cash() const;
    int position() const;

    // Total value given current market price
    double equity(double market_price) const;

    double realized_pnl() const;

private:
    double cash_;
    int position_;
    double realized_pnl_;
};
