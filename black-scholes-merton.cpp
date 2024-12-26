#include "black-scholes-merton.hpp"
#include <cmath>
#include <ctime>

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

double phi(double x) {
    constexpr double one_over_sqrt2 = 0.7071067811865476;
    return (1 + erf(x * one_over_sqrt2)) * 0.5;
}

BlackScholesMerton::BlackScholesMerton() {
    constexpr double years_per_second = 3.1709791983764586E-8;

    S = read_double("Underlying price: ");
    K = read_double("Strike price: ");
    v = read_double("Volatility %: ") / 100;
    r = read_double("Risk-free interest rate %: ") / 100;
    q = read_double("Dividend yield %: ") / 100;
    tm expdate = read_date("Expiration date (mm/dd/yyyy): ");
    const double days = (mktime(&expdate) - time(nullptr)) / (double)86400;
    cout << "Days: " << days << endl;
    t = (mktime(&expdate) - time(nullptr)) * years_per_second;
}

double BlackScholesMerton::call_price() const {
    const D1D2 d = calc_d1d2();
    return S * exp(-q * t) * phi(d.d1) - K * exp(-r * t) * phi(d.d2);
}

double BlackScholesMerton::put_price() const {
    const D1D2 d = calc_d1d2();
    return K * exp(-r * t) * phi(-d.d2) - S * exp(-q * t) * phi(-d.d1);
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

BlackScholesMerton::D1D2 BlackScholesMerton::calc_d1d2() const {
    const double v_times_sqrt_t = v * sqrt(t);
    D1D2 res;
    res.d1 = (log(S / K) + t * (r - q + v * v * 0.5)) / v_times_sqrt_t;
    res.d2 = res.d1 - v_times_sqrt_t;
    return res;
}