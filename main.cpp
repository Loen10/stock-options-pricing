#include "black-scholes-merton.hpp"
#include "inpt.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

int main() {
    while (true) {
        int selection = inpt::read<int>(
            "STOCK OPTIONS PRICING\n"
            "1 - Enter stock options variables\n"
            "2 - View call option pricing details\n"
            "3 - View put option pricing details\n"
            "4 - Select pricing model (default: Black-Scholes-Merton)"
            "0 - Exit program\n"
            "Input: "
        );

        BlackScholesMerton b;
        std::cout << b << std::endl;
        std::cout << "\nTheoretical Call Price: $" << b.call_price() << 
            "\nDelta: " << b.delta_call() <<
            "\nTheta: " << b.theta_call() <<
            "\nRho: " << b.rho_call() <<
            "\nGamma: " << b.gamma() <<
            "\nVega: " << b.vega() <<
            "\n\nTheoretical Put Price: $" << b.put_price() <<
            "\nDelta: " << b.delta_put() <<
            "\nTheta: " << b.theta_put() <<
            "\nRho: " << b.rho_put() << '\n' << std::endl;
    }
}