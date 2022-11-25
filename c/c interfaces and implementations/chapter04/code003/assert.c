#include "assert.h"

cosnt Except_T Assert_Failed = { "Assertion failed" };

void (assert)(int e) {
    assert(e);
}