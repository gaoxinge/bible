#include <stdio.h>
#include "omp.h"

// gcc main.c -fopenmp -o main
int main (int argc, char *argv[]) {
    int nthreads, tid;

#pragma omp parallel private(nthreads, tid) 
    {
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

#pragma omp barrier
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }
}
