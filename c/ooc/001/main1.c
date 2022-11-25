#include <stdio.h>

#include "new.h"
#include "Object.h"
#include "Set.h"

int main() {
    void* s1 = new(Set);
    void* a = add(s1, new(Object));
    void* s2 = new(Set);
    void* b = add(s2, new(Object));
    return 0;
}