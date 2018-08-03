#ifndef RECT_H
#define RECT_H

#include "shape.h"

typedef struct {
    Shape super;
    uint16_t width;
    uint16_t height;
} Rectangle;

void Rectangle_ctor(Rectangle *const me, int16_t x, int16_t y, uint16_t width, uint16_t height);

#endif /* RECT_H */