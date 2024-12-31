#include "inpt.hpp"
#include <limits>

namespace inpt {

bool parse_date(const DateArray& date, tm& result) {
    const char* start = date.data();
    char* end;
    result.tm_mon = strtol(start, &end, 10);

    if (end != start + 2) {
        return false;
    }

    start = end + 1;
    result.tm_mday = strtol(start, &end, 10) - 1;

    if (end != start + 2) {
        return false;
    }

    start = end + 1;
    result.tm_year = strtol(start, &end, 10) - 1900;

    if (end != start + 4) {
        return false;
    }

    return true;
}

void clear_ignore() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void check_eof() {
    if (std::cin.eof()) {
        std::cout << "EOF detected!";
        exit(0);
    }
}

std::istream& operator>>(std::istream& in, std::tm &result) {
    result = std::tm{};
    DateArray date;
    in.read(date.data(), date.size());

    if (in.gcount() != date.size()) {
        in.setstate(in.failbit);
        return in;
    }

    const char* start = date.data();
    char* end;
    result.tm_mon = strtol(start, &end, 10) - 1;

    if (end != start + 2) {
        in.setstate(in.failbit);
        return in;
    }

    start = end + 1;
    result.tm_mday = strtol(start, &end, 10);

    if (end != start + 2) {
        in.setstate(in.failbit);
        return in;
    }

    start = end + 1;
    result.tm_year = strtol(start, &end, 10) - 1900;

    if (end != start + 4) {
        in.setstate(in.failbit);
        return in;
    }

    return in;
}

tm read_date(const char* label) {
    tm result{};

    while (true) {
        std::cout << label;
        DateArray date;
        std::cin.read(date.data(), date.size());
        check_eof();

        if (std::cin.gcount() == date.size() && parse_date(date, result)) {
            return result;
        }

        std::cout << "Invalid input. Please try again" << std::endl;
    }
}
} // namespace inpt