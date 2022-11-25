#include "arith.h"
#include <stdio.h>

int main() {
    printf("%d\n", Arith_div(-13, 5));
    printf("%d\n", Arith_mod(-13, 5));
    printf("%d\n", Arith_ceiling(13, 5));
    printf("%d\n", Arith_ceiling(-13, 5));
    printf("%d\n", Arith_floor(13, 5));
    printf("%d\n", Arith_floor(-13, 5));
    return 0;
}