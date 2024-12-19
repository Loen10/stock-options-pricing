#pragma once
#include <iostream>
#include <string>

using namespace std;

class BlackScholesMerton {
public:
    BlackScholesMerton();
    double call_price() const;
    friend ostream& operator<<(ostream& out, const BlackScholesMerton& b);
private:
    double S, K, v, r, q, t;
};