#include <Python.h>
#include <structmember.h>

typedef struct {
    PyObject_HEAD
    PyObject* hello;
    PyObject* world;
    int spam_id;
} spamObj;

static void spamdealloc(spamObj* self) {
    Py_XDECREF(self->hello);
    Py_XDECREF(self->world);
    self->ob_type
        ->tp_free((PyObject*) self);
}

static PyObject* spamNew(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    spamObj* self = NULL;
    self = (spamObj*) type->tp_alloc(type, 0);
    if (self == NULL)
        goto END;

    self->hello = PyString_FromString("");
    if (self->hello == NULL) {
        Py_XDECREF(self);
        self = NULL;
        goto END;
    }

    self->world = PyString_FromString("");
    if (self->world == NULL) {
        Py_XDECREF(self);
        self = NULL;
        goto END;
    }

    self->spam_id = 0;

END:
    return (PyObject*) self;
}

static int spamInit(spamObj *self, PyObject *args, PyObject *kwds) {
    PyObject* hello = NULL;
    PyObject* world = NULL;
    PyObject* tmp = NULL;

    static char* kwlist[] = {"hello", "world", "spam_id", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist, &hello, &world, &self->spam_id))
        return -1;

    if (hello) {
        tmp = self->hello;
        Py_INCREF(hello);
        self->hello = hello;
        Py_XDECREF(tmp);
    }

    if (world) {
        tmp = self->world;
        Py_INCREF(world);
        self->world = world;
        Py_XDECREF(tmp);
    }

    return 0;
}

static long fib(long n) {
    if (n <= 2)
        return 1;
    return fib(n-1) + fib(n-2);
}

static PyObject* spamFib(spamObj* self, PyObject* args) {
    long arg = 0;

    if (!PyArg_ParseTuple(args, "i", &arg))
        return NULL;

    PyObject* ret = PyInt_FromLong(fib(arg));
    return ret;
}


static PyMemberDef spam_members[] = {
    {"hello", T_OBJECT_EX, offsetof(spamObj, hello), 0, "spam hello"},
    {"world", T_OBJECT_EX, offsetof(spamObj, world), 0, "spam world"},
    {"spam_id", T_INT, offsetof(spamObj, spam_id), 0, "spam id"},
    {NULL}
};

static PyMethodDef spam_methods[] = {
    {"spam_fib", (PyCFunction) spamFib, METH_VARARGS, "Calculate fib number"},
    {NULL}
};

static PyTypeObject spamType = {
    PyObject_HEAD_INIT(NULL)
    0,                               //ob_size
    "spam.SpamType",                 //tp_name
    sizeof(spamObj),                 //tp_basicsize
    0,                               //tp_itemsize
    (destructor) spamdealloc,        //tp_dealloc
    0,                               //tp_print
    0,                               //tp_getattr
    0,                               //tp_setattr
    0,                               //tp_compare
    0,                               //tp_repr
    0,                               //tp_as_number
    0,                               //tp_as_sequence
    0,                               //tp_as_mapping
    0,                               //tp_hash
    0,                               //tp_call
    0,                               //tp_str
    0,                               //tp_getattro
    0,                               //tp_setattro
    0,                               //tp_as_buffer
    Py_TPFLAGS_DEFAULT |
    Py_TPFLAGS_BASETYPE,             //tp_flags
    "spamType objects",              //tp_doc
    0,                               //tp_traverse
    0,                               //tp_clear
    0,                               //tp_richcompare
    0,                               //tp_weaklistoffset
    0,                               //tp_iter
    0,                               //tp_iternext
    spam_methods,                    //tp_methods
    spam_members,                    //tp_members
    0,                               //tp_getset
    0,                               //tp_base
    0,                               //tp_dict
    0,                               //tp_descr_get
    0,                               //tp_descr_set
    0,                               //tp_dictoffset
    (initproc)spamInit,              //tp_init
    0,                               //tp_alloc
    spamNew,                         //tp_new
};

static PyMethodDef module_methods[] = {
    {NULL, NULL, 0, NULL}
};

void initspam() {
    PyObject* m = Py_InitModule("spam", module_methods);

    // add spamType
    if (PyType_Ready(&spamType) < 0)
        return;
    Py_INCREF(&spamType);
    PyModule_AddObject(m, "spam", (PyObject*) &spamType);
}
