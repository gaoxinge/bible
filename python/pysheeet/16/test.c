#include <stdio.h>
#include <stdlib.h>

typedef struct object Obj;
typedef int (*func) (Obj*);

struct object {
    int a;
    int b;
    func add;
    func sub;
};

int add_func(Obj* self) {
    return self->a + self->b;
}

int sub_func(Obj* self) {
    return self->a - self->b;
}

int init_obj(Obj** self) {
    *self = malloc(sizeof(Obj));
    if (*self == NULL)
        return -1;
    (*self)->a = 0;
    (*self)->b = 0;
    (*self)->add = add_func;
    (*self)->sub = sub_func;
    return 0;
}

int main(int argc, char *argv[]) {
    Obj* o = NULL;
    init_obj(&o);
    o->a = 9527;
    o->b = 5566;
    printf("add = %d\n", o->add(o));
    printf("sub = %d\n", o->sub(o));
    return 0;
}