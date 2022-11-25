#include <stdio.h>
#include "Point.h"
#include "Circle.h"
#include "new.h"

int main(int argc, char** argv) {
    void* p;
    
    while (*++argv) {
        switch (**argv) {
            case 'p':
                p = new(Point, 1, 2);
                break;
            case 'c':
                p = new(Circle, 1, 2, 3);
                break;
            default:
                continue;
        }
        draw(p);
        move(p, 10, 20);
        draw(p);
        delete(p);
    }
    
    return 0;
}