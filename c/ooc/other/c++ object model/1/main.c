#include "shape.h"
#include "rectangle.h"
#include "circle.h"
#include <stdio.h>

int main() {
    Rectangle r1, r2;
    Circle    c1, c2;
    
    Rectangle_ctor(&r1,   0, 2, 10, 15);
    Rectangle_ctor(&r2,  -1, 3,  5,  8);
    Circle_ctor(&c1, 1, -2, 12);
    Circle_ctor(&c2, 1, -3,  6);
    
    printf("area of r1 is %d\n", Shape_area(&r1.super));
    printf("area of r2 is %d\n", Shape_area(&r2.super));
    printf("area of c1 is %d\n", Shape_area(&c1.super));
    printf("area of c2 is %d\n", Shape_area(&c2.super));
    
    Shape_draw(&r1.super);
    Shape_draw(&r2.super);
    Shape_draw(&c1.super);
    Shape_draw(&c2.super);
    
    Shape_moveBy(&r1.super, 1, 2);
    Shape_moveBy(&r2.super, 1, 2);
    Shape_moveBy(&c1.super, 1, 2);
    Shape_moveBy(&c2.super, 1, 2);
    
    Shape_draw(&r1.super);
    Shape_draw(&r2.super);
    Shape_draw(&c1.super);
    Shape_draw(&c2.super);
    
    return 0;
}