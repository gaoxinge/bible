#include <iostream>
#include <string>
#include <vector>
#include "absl/strings/str_join.h"

int main() {
    std::vector<std::string> v = {"foo", "bar", "baz"};
    std::string s = absl::StrJoin(v, "-");
    std::cout << s << std::endl;
    return 0;
}
