#pragma once

#include "signal.hpp"

class Portfolio {
public:
    // Portfolio must be born valid
    explicit Portfolio(double initial_cash);

    // Apply an executed trade
    void apply_fill(Signal signal, int quantity, double price);

    // State accessors
    double cash() const;
    int position() const;

    // Valuation
    double equity(double market_price) const;
    double pnl(double market_price) const;

private:
    double cash_;
    int position_;
    double initial_cash_;
};
