#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "value.h"
#include "parse.h"
#include "error.h"

// type
struct Type {
    const char* name;
    int rank, rpar;
    void* (* new)    (va_list ap);
    void  (* exec)   (const void* tree, int rank, int par);
    void  (* delete) (void* tree);
};

void* new(const void* type, ...) {
    assert(type && ((struct Type*) type)->new);
    
    void* result;
    va_list ap;
    va_start(ap, type);
    result = ((struct Type*) type)->new(ap);
    * (const struct Type**) result = type;
    va_end(ap);
    return result;
}

void exec(const void* tree, int rank, int par) {
    assert(tree && 
           * (struct Type**) tree &&
          (* (struct Type**) tree)->exec
    );
    (* (struct Type**) tree)->exec(tree, rank, par);
}

void delete(void* tree) {
    assert(tree && 
           * (struct Type**) tree &&
          (* (struct Type**) tree)->delete
    );
    (* (struct Type**) tree)->delete(tree);
}


// type specific: binary, unary, value
struct Bin {
    const void* type;
    void* left, * right;
};

static void* mkBin(va_list ap) {
    struct Bin* node = malloc(sizeof(struct Bin));
    assert(node);
    node->left  = va_arg(ap, void*);
    node->right = va_arg(ap, void*);
    return node;
}

static void doBin(const void* tree, int rank, int par) {
    const struct Type* type = * (struct Type**) tree;
    par = type->rank < rank || (par && type->rank == rank);
    if (par) putchar('(');
    exec(((struct Bin*) tree)->left, type->rank, 0);
    printf(" %s ", type->name);
    exec(((struct Bin*) tree)->right, type->rank, type->rpar);
    if (par) putchar(')');
}

static void freeBin(void* tree) {
    delete(((struct Bin*) tree)->left);
    delete(((struct Bin*) tree)->right);
    free(tree);
}

static struct Type _Add = {"+", 1, 0, mkBin, doBin, freeBin};
static struct Type _Sub = {"-", 1, 1, mkBin, doBin, freeBin};
static struct Type _Mul = {"*", 2, 0, mkBin, doBin, freeBin};
static struct Type _Div = {"/", 2, 1, mkBin, doBin, freeBin};
const void* Add = &_Add;
const void* Sub = &_Sub;
const void* Mul = &_Mul;
const void* Div = &_Div;


struct Una {
    const void* type;
    void* tn;
};

static void* mkUna(va_list ap) {
    struct Una* node = malloc(sizeof(struct Una));
    assert(node);
    node->tn = va_arg(ap, void*);
    return node;
}

static void doUna(const void* tree, int rank, int par) {
    printf("( -(");
    exec(((struct Una*) tree)->tn, 0, 0);
    printf("))");
}

static void freeUna(void* tree) {
    delete(((struct Una*) tree)->tn);
    free(tree);
}

static struct Type _Minus = {"", 0, 0, mkUna, doUna, freeUna};
const void* Minus = &_Minus;


struct Val {
    const void* type;
    double value;
};

static void* mkVal(va_list ap) {
    struct Val* node = malloc(sizeof(struct Val));
    assert(node);
    node->value = va_arg(ap, double);
    return node;
}

static void doVal(const void* tree, int rank, int par) {
    printf("%f", ((struct Val*) tree)->value);
}

static struct Type _Value = {"", 0, 0, mkVal, doVal, free};
const void* Value = &_Value;


// parser
void* sum() {
    void* result = product();
    const void* type;
    
    for (;;) {
        switch (token) {
            case '+':
                type = Add;
                break;
            case '-':
                type = Sub;
                break;
            default:
                return result;
        }
        scan(0);
        result = new(type, result, product());
    }
}

void* product() {
    void* result = factor();
    const void* type;
    
    for (;;) {
        switch (token) {
            case '*':
                type = Mul;
                break;
            case '/':
                type = Div;
                break;
            default:
                return result;
        }
        scan(0);
        result = new(type, result, factor());
    }
}

void* factor() {
    void* result;
    switch (token) {
        case '+':
            scan(0);
            return factor();
        case '-':
            scan(0);
            return new(Minus, factor());
        case NUMBER:
            result = new(Value, number);
            break;
        case '(':
            scan(0);
            result = sum();
            if (token != ')')
                error("excepting )");
            break;
        default:
            error("bad factor: '%c' 0x%x", token, token);
   }
   scan(0);
   return result;
}


// interpreter
void process(const void* tree) {
    putchar('\t');
    exec(tree, 0, 0);
    putchar('\n');
}