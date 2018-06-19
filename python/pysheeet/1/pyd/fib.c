#include <Python.h>

int _fib(int n) {
    if (n < 2)
        return n;
    return _fib(n - 1) + _fib(n - 2);
}

static PyObject* fib(PyObject* self, PyObject* args) {
    int n;
    int result;
    
    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;
    
    result = _fib(n);
    return Py_BuildValue("i", result);
}

static PyMethodDef LibFibModuleMethods[] = {
    {"fib", fib, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}
};

void initlibfib() {
    (void) Py_InitModule("libfib", LibFibModuleMethods);
}