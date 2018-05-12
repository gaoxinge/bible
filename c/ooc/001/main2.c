#include <stdio.h>

#include "new.h"
#include "Object.h"
#include "Set.h"

int main() {
    void* s1 = new(Set);
    void* a = new(Object);
    void* s2 = new(Set);
    add(s1, a);
    add(s1, s2);
    add(s1, s1);
    return 0;
}