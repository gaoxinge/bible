#include <stdio.h>

#define DECORATOR(t, f, declar, input) \
                                       \
    t decor_##f(declar) {              \
        printf("I am decorator\n");    \
        return f(input);               \
    }
    
#define FUNC_DEC(func, ...) decor_##func(__VA_ARGS__)


void hello(char* str) {
    printf("Hello %s\n", str);
}

#define DECLAR char* str
#define INPUT  str
DECORATOR(void, hello, DECLAR, INPUT)
#undef DECLAR
#undef INPUT


int add(int a, int b) {
    printf("add %d + %d = %d\n", a, b, a + b);
    return a + b;
}

#define DECLAR int a, int b
#define INPUT  a, b
DECORATOR(int, add, DECLAR, INPUT)
#undef DECLAR
#undef INPUT


int main(int argc, char* argv[]) {
    FUNC_DEC(hello, "KerKer");
    FUNC_DEC(add, 1, 2);
    return 0;
}