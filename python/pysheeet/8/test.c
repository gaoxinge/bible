#include <stdio.h>
#include <stdlib.h>

#define ENTER(type, len, ptr)         \
    ptr = malloc(sizeof(type) * len); \
    if (ptr == NULL)                  \
        goto exit;                    \
        
#define EXIT(ptr)                     \
exit:                                 \
    if (ptr != NULL) {                \
        free(ptr);                    \
        ptr = NULL;                   \
    }                                 \
    
#define CONTEXT_MANAGER(t, l, p, ...) { \
    ENTER(t, l, p)                      \
    __VA_ARGS__                         \
    EXIT(p)                             \
}                                       \

int main(int argc, char* argv[]) {
    char* ptr;
    CONTEXT_MANAGER(char, 128, ptr,
        sprintf(ptr, "KerKer");
        printf("%s\n", ptr);
    )
    return 0;
}