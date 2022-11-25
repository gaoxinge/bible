#include <stdio.h>
#include "list.h"

void mkatom(void **x, void *cl) {
    char **str = (char **) x;
    FILE *fp = cl;
    fprintf(fp, "%s ", *str);
    fprintf(fp, "\n");
}

int main() {
    List_T p1 = List_list("Atom", "Mem", "Arena", "List", NULL);
    List_map(p1, mkatom, stderr);
    
    List_T p2 = List_push(NULL, "List");
    p2 = List_push(p2, "Arena");
    p2 = List_push(p2, "Mem");
    p2 = List_push(p2, "Atom");
    List_map(p2, mkatom, stderr);
    
    List_T p3 = List_reverse(List_copy(p2));
    List_map(p3, mkatom, stderr);
    
    return 0;
}