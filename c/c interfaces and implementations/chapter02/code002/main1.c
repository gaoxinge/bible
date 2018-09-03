#include <stdio.h>
#include <stdlib.h>

int main() {
    int *a = malloc(sizeof(int));
    *a = 1;
    printf("%p %p %d\n", &a, a, *a);  // 0061FF2C 00B016D8 1
    free(a);
    printf("%p %p %d\n", &a, a, *a);  // 0061FF2C 00B016D8 11540096
    return 0;
}
