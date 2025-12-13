// Tells the compiler to include this file only once
#pragma once

// Restricted set of values
enum class Signal {
    Buy,
    Sell,
    Hold
};

// No logic just data
struct Order {
    Signal signal;
    int quantity;
    double execution_price;
};

// Signal + the time it was generated
struct TimedSignal {
    Signal signal;
    int execute_day; // day when this signal is allowed to execute
};

class Portfolio; // forward declaration

class ExecutionEngine {
public:
    // Strategy sends signals here
    void accept(const TimedSignal& signal);

    // Engine executes only eligible signals
    // Returns true if an order was executed
    bool execute(
        int day,
        double market_price,
        Portfolio& portfolio,
        Order& out_order
    );

private:
    bool has_pending_signal_ = false;
    TimedSignal pending_signal_;
};
