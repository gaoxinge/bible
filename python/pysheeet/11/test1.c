#include <stdio.h>

// 1
// default
int main() {
    int a = 1;
    switch (a) {
        case 0:
            while (1) {
                printf("0\n");
                break;
                
                case 1:
                    printf("1\n");
                    break;
            }
        default:
            printf("default\n");
    }
    return 0;
}