#pragma once

#include <string>
#include <vector>
#include "market_tick.hpp"

class MarketData {
public:
    explicit MarketData(const std::string& csv_path);

    bool has_next() const;
    MarketTick next();

private:
    std::vector<MarketTick> ticks_;
    std::size_t index_;
};
