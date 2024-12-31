#pragma once
#include <array>
#include <iostream>
#include <ctime>

namespace inpt {
using DateArray = std::array<char, 10>;

void clear_ignore();
void check_eof();
std::istream& operator>>(std::istream& in, std::tm& date);
std::tm read_date(const char* label);

template<typename T>
T read(const char* label) {
    while (true) {
        std::cout << label;
        T t;
        std::cin >> t;
        check_eof();
        const bool success = !std::cin.fail();
        clear_ignore();

        if (success) {
            return t;
        }
        
        std::cout << "Invalid input. Please try again" << std::endl;
    }
}

} // namespace inpt



