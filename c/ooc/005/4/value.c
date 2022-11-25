#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "value.h"
#include "parse.h"
#include "error.h"

// type
struct Type {
    void*  (* new)    (va_list ap);
    double (* exec)   (const void* tree);
    void   (* delete) (void* tree);
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

double exec(const void* tree) {
    return (* (struct Type **) tree)->exec(tree);
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

static double doAdd(const void* tree) {
    return exec(((struct Bin*) tree)->left) +
           exec(((struct Bin*) tree)->right);
}

static double doSub(const void* tree) {
    return exec(((struct Bin*) tree)->left) -
           exec(((struct Bin*) tree)->right);
}

static double doMul(const void* tree) {
    return exec(((struct Bin*) tree)->left) *
           exec(((struct Bin*) tree)->right);
}

static double doDiv(const void* tree) {
    return exec(((struct Bin*) tree)->left) /
           exec(((struct Bin*) tree)->right);
}

static void freeBin(void* tree) {
    delete(((struct Bin*) tree)->left);
    delete(((struct Bin*) tree)->right);
    free(tree);
}

static struct Type _Add = {mkBin, doAdd, freeBin};
static struct Type _Sub = {mkBin, doSub, freeBin};
static struct Type _Mul = {mkBin, doMul, freeBin};
static struct Type _Div = {mkBin, doDiv, freeBin};
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

static double doUna(const void* tree) {
    return -exec(((struct Una*) tree)->tn);
}

static void freeUna(void* tree) {
    delete(((struct Una*) tree)->tn);
    free(tree);
}

static struct Type _Minus = {mkUna, doUna, freeUna};
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

static double doVal(const void* tree) {
    return ((struct Val*) tree)->value;
}

static struct Type _Value = {mkVal, doVal, free};
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
    printf("\t%g\n", exec(tree));
}