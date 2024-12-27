#include "black-scholes-merton.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    cout << "STOCK OPTIONS PRICING" << endl;

    while (true) {
        BlackScholesMerton b;
        cout << "Theoretical Call Price: $" << b.call_price() << 
            "\nDelta: " << b.delta_call() <<
            "\nTheta: " << b.theta_call() <<
            "\nRho: " << b.rho_call() <<
            "\nGamma: " << b.gamma() <<
            "\nVega: " << b.vega() <<
            "\n\nTheoretical Put Price: $" << b.put_price() <<
            "\nDelta: " << b.delta_put() <<
            "\nTheta: " << b.theta_put() <<
            "\nRho: " << b.rho_put() << endl;
    }
}