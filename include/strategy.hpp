#pragma once

#include "execution.hpp"
#include <vector>

class Strategy {
public:
    // Memory must start in a known state
    Strategy();

    // Observe market data at time t
    // Possibly submit a signal
    void on_day(
        int time_index,
        const std::vector<double>& prices,
        // Strategy does not own the execution engine
        // It only talks to it
        ExecutionEngine& execution
    );

private:
    bool has_position_;
};
