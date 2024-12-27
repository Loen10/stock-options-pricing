#include "black-scholes-merton.hpp"
#include <cmath>
#include <ctime>


// 0x3FD9884533D43651
constexpr double invsqrt2 = 0.70710678118654752440084436210485;
constexpr double invsqrt2pi = 0.39894228040143267793994605993438;
constexpr double years_per_day = 0.00273972602739726027397260273973;

constexpr double sncdf(const double x) {
    return 0.5 * (1 + erf(x * invsqrt2));
}

constexpr double snpdf(const double x) {
    return invsqrt2pi * exp(-(x * x) * 0.5);
}

double read_double(const char* label) {
    while (true) {
        cout << label;
        string input;
        getline(cin, input);
        char* end;
        double result = strtod(input.c_str(), &end);
        
        if (end != input.c_str()) {
            return result;
        }

        cout << "Invalid input!" << endl;
    }
}

tm read_date(const char* label) {
    tm result{};

    while (true) {
        cout << label;
        string input;
        getline(cin, input);
        const char* start = input.c_str();
        char* end;
        result.tm_mon = strtol(start, &end, 10) - 1;

        if (end != start + 2) {
            cout << "Invalid input!" << endl;
            continue;
        }

        start = end + 1;
        result.tm_mday = strtol(start, &end, 10);

        if (end != start + 2) {
            cout << "Invalid input!" << endl;
            continue;
        }

        start = end + 1;
        result.tm_year = strtol(start, &end, 10) - 1900;

        if (end != start + 4) {
            cout << "Invalid input!" << endl;
            continue;
        }

        return result;
    }
}

BlackScholesMerton::BlackScholesMerton() {
    constexpr double years_per_second = 3.1709791983764586E-8;

    S = read_double("Underlying price: ");
    K = read_double("Strike price: ");
    v = read_double("Volatility %: ") / 100;
    r = read_double("Risk-free interest rate %: ") / 100;
    q = read_double("Dividend yield %: ") / 100;
    
    tm expdate = read_date("Expiration date (mm/dd/yyyy): ");
    t = (mktime(&expdate) - time(nullptr)) * years_per_second;

    v_sqrt_t = v * sqrt(t);
    d1 = (log(S / K) + t * (r - q + v * v * 0.5)) / v_sqrt_t;
    d2 = d1 - v_sqrt_t;
}

double BlackScholesMerton::call_price() const {
    return S * exp(-q * t) * sncdf(d1) - K * exp(-r * t) * sncdf(d2);
}

double BlackScholesMerton::put_price() const {
    return K * exp(-r * t) * sncdf(-d2) - S * exp(-q * t) * sncdf(-d1);
}

double BlackScholesMerton::delta_call() const {
    return exp(-q * t) * sncdf(d1);
}

double BlackScholesMerton::delta_put() const {
    return exp(-q * t) * (sncdf(d1) - 1);
}

double BlackScholesMerton::gamma() const {
    return exp(-q * t) / (S * v_sqrt_t) * snpdf(d1);
}

double BlackScholesMerton::theta_call() const {
    return years_per_day * (
        theta_base() - r * K * exp(-r * t) * sncdf(d2) +
            q * S * exp(-q * t) * sncdf(d1)
    );
}

double BlackScholesMerton::theta_put() const {
    return years_per_day * (
        theta_base() + r * K * exp(-r * t) * sncdf(-d2) -
            q * S * exp(-q * t) * sncdf(-d1)
    );
}

double BlackScholesMerton::vega() const {
    return 0.01 * S * exp(-q * t) * sqrt(t) * snpdf(d1);
}

double BlackScholesMerton::rho_call() const {
    return 0.01 * K * t * exp(-r * t) * sncdf(d2);
}

double BlackScholesMerton::rho_put() const {
    return -0.01 * K * t * exp(-r * t) * sncdf(-d2);
}

double BlackScholesMerton::theta_base() const {
    return -(S * v * exp(-q * t) / (2 * sqrt(t)) * snpdf(d1));
}

ostream& operator<<(ostream& out, const BlackScholesMerton& b) {
    out << "Underlying price: " << b.S <<
        "\nStrike price: " << b.K <<
        "\nVolatility: " << b.v <<
        "\nRisk-free interest rate: " << b.r * 100 << "%"
        "\nDividend yield: " << b.q * 100 << "%"
        "\nDays to expiration: " << b.t * 365;
    
    return out;
}