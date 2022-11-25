#include <stdio.h>

int main(int argc, char* argv[]) {
    int a = 123;
    void* x[3] = {"Hello", "World", &a};
    printf("%s %s %d\n", x[0], x[1], * (int*) x[2]);
    return 0;
}