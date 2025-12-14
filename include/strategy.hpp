#pragma once

#include "signal.hpp"

class Strategy {
public:
    Strategy();

    Signal on_price(double price) const;

private:
    double last_price_;
};
