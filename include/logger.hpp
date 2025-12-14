#pragma once

#include <fstream>
#include "market_tick.hpp"
#include "portfolio.hpp"
#include "execution.hpp"

class Logger {
public:
    explicit Logger(const std::string& output_path);

    void log_tick(
        const MarketTick& tick,
        const Portfolio& portfolio,
        const ExecutionEngine& execution
    );

private:
    void write_header();

    std::ofstream file_;
    bool header_written_;
};
