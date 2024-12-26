#include "black-scholes-merton.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    cout << "STOCK OPTIONS PRICING" << endl;
    BlackScholesMerton b;
    cout << "Theoretical Call Price: $" << b.call_price() << endl;
    cout << "Theoretical Put Price: $" << b.put_price() << endl;
}