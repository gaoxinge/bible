#include "rectangle.h"
#include <stdio.h>

static uint32_t Rectangle_area_(const Shape *const me) {
    const Rectangle *const me_ = (const Rectangle *) me;
    return (uint32_t) me_->width * (uint32_t) me_->height;
}

static void Rectangle_draw_(const Shape *const me) {
    const Rectangle *const me_  = (const Rectangle *const) me;
    printf("Rectangle_draw_(x = %d, y = %d, width = %d, height = %d)\n", 
           me_->super.x, me_->super.y, me_->width, me_->height);
}

static struct ShapeVtbl vtbl = {
    Rectangle_area_,
    Rectangle_draw_,
};

void Rectangle_ctor(Rectangle *const me, int16_t x, int16_t y,
                    uint16_t width, uint16_t height) {
    Shape_ctor(&me->super, x, y);    
    me->super.vptr = &vtbl;
    me->width = width;
    me->height = height;
}
