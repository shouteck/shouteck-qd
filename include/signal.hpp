#pragma once

#include "signal.hpp"

struct PendingOrder {
    Signal side;      // Buy or Sell
    int quantity;     // shares
};
