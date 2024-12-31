#include "black-scholes-merton.hpp"
#include "inpt.hpp"
#include <cmath>
#include <ctime>
#include <array>

constexpr double invsqrt2 = 0.70710678118654752440084436210485;
constexpr double invsqrt2pi = 0.39894228040143267793994605993438;
constexpr double years_per_day = 0.00273972602739726027397260273973;

constexpr double sncdf(const double x) {
    return 0.5 * (1 + erf(x * invsqrt2));
}

constexpr double snpdf(const double x) {
    return invsqrt2pi * exp(-(x * x) * 0.5);
}

BlackScholesMerton::BlackScholesMerton() {
    constexpr double years_per_second = 3.1709791983764586E-8;

    S = inpt::read<double>("Underlying price: ");
    K = inpt::read<double>("Strike price: ");
    v = inpt::read<double>("Volatility %: ") / 100;
    r = inpt::read<double>("Risk-free interest rate %: ") / 100;
    q = inpt::read<double>("Dividend yield %: ") / 100;
    
    std::tm expdate = inpt::read<std::tm>("Expiration date (mm/dd/yyyy): ");
    t = (std::mktime(&expdate) - std::time(nullptr)) * years_per_second;

    v_sqrt_t = v * std::sqrt(t);
    d1 = (log(S / K) + t * (r - q + v * v * 0.5)) / v_sqrt_t;
    d2 = d1 - v_sqrt_t;
}

double BlackScholesMerton::call_price() const {
    return S * std::exp(-q * t) * sncdf(d1) - K * std::exp(-r * t) * sncdf(d2);
}

double BlackScholesMerton::put_price() const {
    return K * std::exp(-r * t) * sncdf(-d2) -
        S * std::exp(-q * t) * sncdf(-d1);
}

double BlackScholesMerton::delta_call() const {
    return std::exp(-q * t) * sncdf(d1);
}

double BlackScholesMerton::delta_put() const {
    return std::exp(-q * t) * (sncdf(d1) - 1);
}

double BlackScholesMerton::gamma() const {
    return std::exp(-q * t) / (S * v_sqrt_t) * snpdf(d1);
}

double BlackScholesMerton::theta_call() const {
    return years_per_day * (
        theta_base() - r * K * std::exp(-r * t) * sncdf(d2) +
            q * S * std::exp(-q * t) * sncdf(d1)
    );
}

double BlackScholesMerton::theta_put() const {
    return years_per_day * (
        theta_base() + r * K * std::exp(-r * t) * sncdf(-d2) -
            q * S * std::exp(-q * t) * sncdf(-d1)
    );
}

double BlackScholesMerton::vega() const {
    return 0.01 * S * std::exp(-q * t) * sqrt(t) * snpdf(d1);
}

double BlackScholesMerton::rho_call() const {
    return 0.01 * K * t * std::exp(-r * t) * sncdf(d2);
}

double BlackScholesMerton::rho_put() const {
    return -0.01 * K * t * std::exp(-r * t) * sncdf(-d2);
}

double BlackScholesMerton::theta_base() const {
    return -(S * v * std::exp(-q * t) / (2 * sqrt(t)) * snpdf(d1));
}

std::ostream& operator<<(std::ostream& out, const BlackScholesMerton& b) {
    out << "Underlying price: " << b.S <<
        "\nStrike price: " << b.K <<
        "\nVolatility: " << b.v * 100 << "%"
        "\nRisk-free interest rate: " << b.r * 100 << "%"
        "\nDividend yield: " << b.q * 100 << "%"
        "\nDays to expiration: " << b.t * 365;
    
    return out;
}