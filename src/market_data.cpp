#include "market_data.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {

bool is_regular_market_hours(const std::string& timestamp) {
    int hour = std::stoi(timestamp.substr(11, 2));
    int minute = std::stoi(timestamp.substr(14, 2));

    if (hour < 9 || hour > 16) return false;
    if (hour == 9 && minute < 30) return false;
    if (hour == 16 && minute > 0) return false;

    return true;
}

}

MarketData::MarketData(const std::string& csv_path)
    : index_(0)
{
    std::ifstream file(csv_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open market data CSV");
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string timestamp, price_str;

        std::getline(ss, timestamp, ',');
        std::getline(ss, price_str, ',');

        if (!is_regular_market_hours(timestamp)) {
            continue;
        }

        ticks_.push_back({
            timestamp,
            std::stod(price_str)
        });
    }
}

bool MarketData::has_next() const {
    return index_ < ticks_.size();
}

MarketTick MarketData::next() {
    return ticks_.at(index_++);
}
