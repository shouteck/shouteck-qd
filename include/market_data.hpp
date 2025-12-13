#pragma once

#include <string>
#include <vector>

// One market event (price + time)
struct MarketTick {
    std::string timestamp; // "YYYY-MM-DD HH:MM:SS"
    double price;
};

// Load CSV and return only regular-session ticks
std::vector<MarketTick> load_market_data(const std::string& csv_path);
