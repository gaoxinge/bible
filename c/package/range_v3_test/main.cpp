#include <iostream>
#include <string>
#include "range/v3/all.hpp"

int main() {
    std::string s{"hello"};
    ranges::for_each(s, [](char c) { std::cout << c << " "; });
    std::cout << std::endl;
    return 0;
}
