#include "market_data.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

// Helper: check if timestamp is within US regular hours
static bool is_regular_market_hours(const std::string& timestamp) {
    // timestamp format assumed: "YYYY-MM-DD HH:MM:SS"
    // We only care about HH:MM
    std::string time = timestamp.substr(11, 5); // HH:MM

    return time >= "09:30" && time <= "16:00";
}

std::vector<MarketTick> load_market_data(const std::string& csv_path) {
    std::vector<MarketTick> ticks;
    std::ifstream file(csv_path);

    if (!file) {
        std::cerr << "Failed to open CSV: " << csv_path << "\n";
        return ticks;
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string timestamp;
        std::string price_str;

        std::getline(ss, timestamp, ',');
        std::getline(ss, price_str, ',');

        if (!is_regular_market_hours(timestamp)) {
            continue;
        }

        MarketTick tick;
        tick.timestamp = timestamp;
        tick.price = std::stod(price_str);

        ticks.push_back(tick);
    }

    return ticks;
}
