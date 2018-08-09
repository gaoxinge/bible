#include <stdio.h>

int main() {
    int a = 1;
    long b = 5000L;
    
    float c = 2.0;
    double d = 0.3;
    
    float e = 1.0e+33;
    double f = 1.0e-33;
    
    int g = 077;
    int h = 0xACE;
    
    printf("%d\n", a);
    printf("%ld\n", b);
    
    printf("%.1f\n", c);
    printf("%.1lf\n", d);
    
    printf("%.1f\n", e);
    printf("%.1lf\n", f);
    
    printf("%#O\n", g);
    printf("%#X\n", h);
    
    return 0;
}