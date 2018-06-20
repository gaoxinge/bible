#include <stdio.h>

#define foreach(it, x, ...) \
    for (char** it = x; *it; it++) {__VA_ARGS__}
    
int main(int argc, char* argv[]) {
    char* x[] = {"Hello", "World", "!!!", NULL};
    foreach(it, x, printf("%s ", *it);)
    return 0;    
}