#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "Point.h"
#include "new.h"
#include "new.r"

struct Point {
    const void* class;
    int x, y;
};

static void* Point_ctor(void* _self, va_list* app) {
    struct Point* self = _self;
    self->x = va_arg(*app, int);
    self->y = va_arg(*app, int);
    return self;
}

static int Point_differ(const void* _self, const void* _b) {
    const struct Point* self = _self;
    const struct Point* b = _b;
    
    if (self == b)
        return 0;
    
    if (!b || b->class != Point)
        return 1;
    
    return self->x != b->x || self->y != b->y;
}

static void Point_draw(const void* _self) {
    const struct Point* self = _self;
    printf("\".\" at %d,%d\n", self->x, self->y);
}

static const struct Class _Point = {
    sizeof(struct Point),
    Point_ctor,
    0,
    0,
    Point_differ,
    Point_draw
};

const void* Point = &_Point;

void move(void* _self, int dx, int dy) {
    struct Point* self = _self;
    self->x += dx;
    self->y += dy;
}