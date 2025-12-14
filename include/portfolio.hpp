#pragma once

class Portfolio {
public:
    explicit Portfolio(double initial_cash);

    double cash() const;
    int position() const;

    double equity(double price) const;
    double pnl(double price) const;

    int max_affordable_quantity() const;

    void buy(int quantity, double price);
    void sell(int quantity, double price);

private:
    double cash_;
    int position_;
    double initial_cash_;
};
