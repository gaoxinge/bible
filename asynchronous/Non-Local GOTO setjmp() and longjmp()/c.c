#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#define MAX_COUNT 5

typedef struct PCB_NODE *PCB_ptr;

typedef struct PCB_NODE {
    jmp_buf Environment;
    int Name;
    PCB_ptr Next;
} PCB;

jmp_buf MAIN;
jmp_buf SCHEDULER;

PCB_ptr Head;
PCB_ptr Current;
PCB_ptr work;

#define THREAD_CREATE(function, name) \
{                                     \
    if (setjmp(MAIN) == 0)            \
        (function)(name);             \
}

#define THREAD_INIT(name)                 \
{                                         \
    work = (PCB_ptr) malloc(sizeof(PCB)); \
    work->Name = name;                    \
    if (Head == NULL)                     \
        Head = work;                      \
    else                                  \
        Current->Next = work;             \
    work->Next = Head;                    \
    Current = work;                       \
    if (setjmp(work->Environment) == 0)   \
        longjmp(MAIN, 1);                 \
}

#define THREAD_YIELD(name)                 \
{                                          \
    if (setjmp(Current->Environment) == 0) \
        longjmp(SCHEDULER, 1);             \
}

#define THREAD_EXIT(name)                 \
{                                         \
    if (Current->Next == Current) {       \
        free(Current);                    \
        Current = NULL;                   \
    } else {                              \
        work = Current;                   \
        while (work->Next != Current)     \
            work = work->Next;            \
        work->Next = Current->Next;       \
        free(Current);                    \
        Current = work;                   \
    }                                     \
    longjmp(SCHEDULER, 1);                \
}

int i1;
int i2;
int i3;
int i4;

void funct_1(int name) {
    
    THREAD_INIT(name);
    for (i1 = 1; i1 <= MAX_COUNT; i1++) {
        printf("funct_1() executing %d\n", i1);
        THREAD_YIELD(name);
    }
    THREAD_EXIT(name);
}

void funct_2(int name) {
    
    THREAD_INIT(name);
    for (i2 = 1; i2 <= MAX_COUNT; i2++) {
        printf("funct_2() executing %d\n", i2);
        THREAD_YIELD(name);
    }
    THREAD_EXIT(name);
}

void funct_3(int name) {

    THREAD_INIT(name);
    for (i3 = 1; i3 <= MAX_COUNT; i3++) {
        printf("funct_3() executing %d\n", i3);
        THREAD_YIELD(name);
    }
    THREAD_EXIT(name);
}

void funct_4(int name) {

    THREAD_INIT(name);
    for (i4 = 1; i4 <= MAX_COUNT; i4++) {
        printf("funct_4() executing %d\n", i4);
        THREAD_YIELD(name);
    }
    THREAD_EXIT(name);
}

void Scheduler() {
    if (setjmp(SCHEDULER) == 0)
        longjmp(MAIN, 1);
    if (Current != NULL) {
        Current = Current->Next;
        longjmp(Current->Environment, 1);
    }
}

void main() {
    Head = Current = NULL;
    
    THREAD_CREATE(funct_1, 1);
    THREAD_CREATE(funct_2, 2);
    THREAD_CREATE(funct_3, 3);
    THREAD_CREATE(funct_4, 4);
    
    if (setjmp(MAIN) == 0)
        Scheduler();
    longjmp(SCHEDULER, 1);
}