// Tells the compiler to include this file only once
#pragma once

#include <string>

// Restricted set of values
enum class Signal {
    Buy,
    Sell,
    Hold
};

// No logic just data
struct Order {
    Signal signal;
    std::string execution_date;
    double execution_price;
};

class ExecutionEngine {
public:
    // Submit a signal generated at time t
    void submit(Signal signal);

    // Execute pending signal using the bar at time t+1
    // Returns true if an order was executed
    bool execute(
        // Pass by reference to avoid copying the string, saving memory
        const std::string& date,
        double open_price,
        Order& out_order
    );

    bool has_pending() const;

private:
    bool has_pending_signal_ = false;
    Signal pending_signal_;
};
