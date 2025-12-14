#pragma once

class Portfolio {
public:
    explicit Portfolio(double initial_cash);

    void apply_fill(const PendingOrder& order, double price);

    double cash() const;
    int position() const;
    double equity(double price) const;
    double initial_cash() const;

private:
    double cash_;
    int position_;
    double initial_cash_;
};
