#include <iostream>
#include "magic_enum.hpp"

enum class Color { RED = 2, BLUE = 4, GREEN = 8 };

int main() {
    Color color = Color::RED;
    auto color_name = magic_enum::enum_name(color);
    std::cout << color_name << std::endl;
    return 0;
}
