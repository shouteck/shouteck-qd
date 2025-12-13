#pragma once

#include "signal.hpp"

// Given a signal and a price, can we execute it safely?

class Portfolio;

class ExecutionEngine {
public:
    bool execute(
        Signal signal,
        double market_price,
        Portfolio& portfolio
    );
};
