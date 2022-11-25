#include <Python.h>

typedef struct {
    PyObject_HEAD
} spamObj;

static PyTypeObject spamType = {
    PyObject_HEAD_INIT(&PyType_Type)
    0,                  //ob_size
    "spam.Spam",        //tp_name
    sizeof(spamObj),    //tp_basicsize
    0,                  //tp_itemsize
    0,                  //tp_dealloc
    0,                  //tp_print
    0,                  //tp_getattr
    0,                  //tp_setattr
    0,                  //tp_compare
    0,                  //tp_repr
    0,                  //tp_as_number
    0,                  //tp_as_sequence
    0,                  //tp_as_mapping
    0,                  //tp_hash
    0,                  //tp_call
    0,                  //tp_str
    0,                  //tp_getattro
    0,                  //tp_setattro
    0,                  //tp_as_buffer
    Py_TPFLAGS_DEFAULT, //tp_flags
    "spam objects",     //tp_doc
};

static PyMethodDef spam_methods[] = {
    {NULL, NULL, 0, NULL}  
};

void initspam() {
    PyObject* m = Py_InitModule("spam", spam_methods);
    
    // add spamType
    spamType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&spamType) < 0)
        return;
    Py_INCREF(&spamType);
    PyModule_AddObject(m, "spam", (PyObject*) &spamType);
}