#ifndef SHAPE_H
#define SHAPE_H

#include <stdint.h>

struct ShapeVtbl;

typedef struct {
    const struct ShapeVtbl *vptr;
    int16_t x;
    int16_t y;
} Shape;

struct ShapeVtbl {
    uint32_t (*area) (const Shape *const me);
    void     (*draw) (const Shape *const me);
};

void     Shape_ctor     (Shape *const me, int16_t x, int16_t y);    // inheritance: in subclass
void     Shape_moveBy   (Shape *const me, int16_t dx, int16_t dy);  // inheritance: in main
uint32_t Shape_area     (const Shape *const me);                    // polymorphism
void     Shape_draw     (const Shape *const me);                    // polymorphism

#endif /* SHAPE_H */