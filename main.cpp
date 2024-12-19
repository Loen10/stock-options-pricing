#include "black-scholes-merton.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    cout << "STOCK OPTIONS PRICING" << endl;
    BlackScholesMerton b;
    cout << b.call_price() << endl;
}