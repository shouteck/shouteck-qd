#include "logger.hpp"

Logger::Logger(const std::string& output_path)
    : header_written_(false)
{
    file_.open(output_path);
}

void Logger::write_header() {
    file_ << "timestamp,price,cash,position,equity,pnl,has_pending\n";
    header_written_ = true;
}

void Logger::log_tick(
    const MarketTick& tick,
    const Portfolio& portfolio,
    const ExecutionEngine& execution
) {
    if (!header_written_) {
        write_header();
    }

    double equity = portfolio.equity(tick.price);
    double pnl = equity - portfolio.initial_cash();

    file_
        << tick.timestamp << ","
        << tick.price << ","
        << portfolio.cash() << ","
        << portfolio.position() << ","
        << equity << ","
        << pnl << ","
        << execution.has_pending_order()
        << "\n";
}
