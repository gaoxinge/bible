#include <iostream>
#include <string>

#define STB_SPRINTF_IMPLEMENTATION
#include "stb_sprintf.h"

#define STB_DIVIDE_IMPLEMENTATION
#include "stb_divide.h"

int main() {
    char buf[1024];
    stbsp_sprintf(buf, "%c %s     %d", 'a', "b", 1);
    std::string s(buf);
    std::cout << s << std::endl;

    std::cout << stb_div_trunc(3, 2) << std::endl;
    
    return 0;
}
