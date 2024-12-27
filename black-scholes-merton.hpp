#pragma once
#include <iostream>
#include <string>

using namespace std;

class BlackScholesMerton {
public:
    BlackScholesMerton();

    double call_price() const;
    double put_price() const;
    double delta_call() const;
    double delta_put() const;
    double gamma() const;
    double theta_call() const;
    double theta_put() const;
    double vega() const;
    double rho_call() const;
    double rho_put() const;

    friend ostream& operator<<(ostream& out, const BlackScholesMerton& b);
private:
    double S, K, v, r, q, t, v_sqrt_t, d1, d2;

    double theta_base() const;
};