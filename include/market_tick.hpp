#pragma once
#include <string>

struct MarketTick {
    std::string timestamp; // "YYYY-MM-DD HH:MM:SS" (ET)
    double price;
};
