#include "shape.h"
#include <assert.h>

static uint32_t Shape_area_(const Shape *const me) {
    assert(0);
    return 0U;
}

static void Shape_draw_(const Shape *const me) {
    assert(0);
}

static struct ShapeVtbl vtbl = {
    Shape_area_,
    Shape_draw_,
};

void Shape_ctor(Shape *const me, int16_t x, int16_t y) {
    me->vptr = &vtbl;
    me->x = x;
    me->y = y;
}

void Shape_moveBy(Shape *const me, int16_t x, int16_t y) {
    me->x += x;
    me->y += y;
}

uint32_t Shape_area(const Shape *const me) {
    return (me->vptr->area)(me);
}

void Shape_draw(const Shape *const me) {
    (me->vptr->draw)(me);
}