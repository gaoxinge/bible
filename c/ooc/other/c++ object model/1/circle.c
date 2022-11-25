#include "circle.h"
#include <stdio.h>

static uint32_t Circle_area_(const Shape *const me) {
    const Circle *const me_ = (const Circle *) me;
    return 3L * (uint32_t) me_->radius * (uint32_t) me_->radius;
}

static void Circle_draw_(const Shape *const me) {
    const Circle *const me_ = (const Circle *) me;
    printf("Circle_draw_(x = %d, y = %d, radius = %d)\n", 
           me_->super.x, me_->super.y, me_->radius);
}

static struct ShapeVtbl vtbl = {
    Circle_area_,
    Circle_draw_,
};

void Circle_ctor(Circle *const me, int16_t x, int16_t y, uint16_t radius) {
    Shape_ctor(&me->super, x, y);
    me->super.vptr = &vtbl;
    me->radius = radius;
}