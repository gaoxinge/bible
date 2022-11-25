#include "atom.h"
#include <stdio.h>

int main() {
    const char *a = Atom_new("abc", 3);
    const char *b = Atom_string("abcd");
    const char *c = Atom_int(1234L);
    printf("%d %d %d", Atom_length(a), Atom_length(b), Atom_length(c));
    return 0;
}