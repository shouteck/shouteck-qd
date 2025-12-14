#pragma once

#include "signal.hpp"

class Strategy {
public:
    Strategy();

    Signal on_tick(double price);
};
