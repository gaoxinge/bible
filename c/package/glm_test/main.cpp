#include <iostream>
#include "glm/vec3.hpp"

int main() {
    glm::vec3 v(1, 2, 3);
    std::cout << v.x << " " << v.y << " " << v.z << std::endl;
    return 0;
}
