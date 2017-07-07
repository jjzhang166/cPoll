#ifndef CPOOL_H__
#define CPOOL_H__

#include "Python.h"

void PyComplete_cPool(void *m);

static PyModuleDef cPoolModule = {
    PyModuleDef_HEAD_INIT,
    "cPool",
    "cPool is nextgen multiplexer class system",
    -1,
    NULL,
    NULL,
    NULL,
    NULL,
    PyComplete_cPool    /* A function to call during deallocation of the module object, or NULL if not needed. */
};

#endif /* CPOOL_H__ */
