#include <stdio.h>

#define FUNC(...) base_func((struct input) {.var=0, ##__VA_ARGS__});

struct input {
    char* str;
    double dvar;
    int var;
};

void base_func(struct input in) {
    printf("%s %lf %d\n", in.str, in.dvar, in.var);
}

int main(int argc, char* argv[]) {
    FUNC(.str="KerKer", .dvar=2.0, 2);
    FUNC(.str="HaHa",   .dvar=3.0);
    return 0;
} 