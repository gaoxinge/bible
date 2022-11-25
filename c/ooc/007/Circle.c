#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "Circle.h"
#include "Circle.r"
#include "new.h"
#include "new.r"

static void* Circle_ctor(void* _self, va_list* app) {
    struct Circle* self = ((const struct Class*) Point) -> ctor(_self, app);
    self->rad = va_arg(*app, int);
    return self;
}

static int Circle_differ(const void* _self, const void* _b) {
    return 0;  // pass 
}

static void Circle_draw(const void* _self) {
    const struct Circle* self = _self;
    printf("Circle at %d,%d rad %d\n", x(self), y(self), self->rad);
}

static const struct Class _Circle = {
    sizeof(struct Circle),
    Circle_ctor,
    0,
    0,
    Circle_differ,
    Circle_draw
};

const void* Circle = &_Circle;
