#include <stdio.h>

typedef void (*func)(void);

void func_1() {
    printf("Hello\n");
}

void func_2() {
    printf("World\n");
}

void func_3() {
    printf("!!!\n");
}

int main(int argc, char* argv[]) {
    func s[] = {func_1, func_2, func_3};
    for (int i = 0; i < 3; i++)
        s[i]();
    return 0;
}