#pragma once
#include <iostream>
#include <string>

using namespace std;

class BlackScholesMerton {
public:
    BlackScholesMerton();
    double call_price() const;
    double put_price() const;
    friend ostream& operator<<(ostream& out, const BlackScholesMerton& b);
private:
    double S, K, v, r, q, t;

    struct D1D2 {
        double d1, d2;
    };

    D1D2 calc_d1d2() const;
};