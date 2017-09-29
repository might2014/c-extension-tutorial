#include <Python.h>
#include <stdio.h>

static unsigned long
cfib(unsigned long n)
{
    unsigned long a = 1;
    unsigned long b = 1;
    unsigned long c;

    if (n <= 1) {
        return 1;
    }

    while (--n > 1) {
        c = a + b;
        a = b;
        b = c;
    }

    return b;
}

PyDoc_STRVAR(fib_doc, "compute the nth Fibonacci number");

static PyObject*
pyfib(PyObject* self, PyObject* n)
{
    
    unsigned long as_unsigned_long = PyLong_AsUnsignedLong(n);
    if(PyErr_Occurred() != NULL)
    {
	return NULL;

    }   

    PyObject* a = PyLong_FromUnsignedLong(1);
    PyObject* b = PyLong_FromUnsignedLong(1);
    PyObject* c = NULL;

    if (as_unsigned_long <= 1) {
        Py_XDECREF(a);
        Py_XDECREF(b);
        Py_XDECREF(c);
        return PyLong_FromUnsignedLong(1);
    }

    while (--as_unsigned_long > 1) {
        printf("%lu\n", as_unsigned_long);
        if(c != NULL)
        {
            printf("%s, %d\n",__FILE__, __LINE__);
            Py_XDECREF(c);
        }

        printf("%s, %d\n",__FILE__, __LINE__);
        c = PyNumber_Add(a, b);
        if(c == NULL)
        {
            return NULL;
        }

        printf("%s, %d\n",__FILE__, __LINE__);
        Py_XDECREF(a);
        printf("%s, %d\n",__FILE__, __LINE__);
        a = b;
        printf("%s, %d\n",__FILE__, __LINE__);
        //b equal to a now, probably why this is crashing
        Py_XDECREF(b);
        printf("%s, %d\n",__FILE__, __LINE__);
        b = c;
    }

    printf("%s, %d\n",__FILE__, __LINE__);
    Py_XDECREF(a);
    printf("%s, %d\n",__FILE__, __LINE__);
    //c equal to b now, this will cause result to be de-allocated
    //Py_XDECREF(c);
    return b;

    /*
     *
     * TODO: add GOTO error handling for ref counting cleanup
     */

    //PyObject* result = PyLong_FromUnsignedLong(cfib(as_unsigned_long));
    //return result;

}

PyMethodDef methods[] = {
    {"fib", (PyCFunction) pyfib, METH_O, fib_doc},
    {NULL},
};

PyDoc_STRVAR(fib_module_doc, "provides a Fibonacci function");

PyModuleDef fib_module = {
    PyModuleDef_HEAD_INIT,
    "fib",
    fib_module_doc,
    -1,
    methods,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC
PyInit_fib(void)
{
    return PyModule_Create(&fib_module);
}
