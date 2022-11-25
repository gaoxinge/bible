#include <stdio.h>
#include "uv.h"

int main() {
    printf("No quitting.\n");
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    uv_loop_close(uv_default_loop());
    return 0;
}