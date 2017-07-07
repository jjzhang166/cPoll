#ifndef WINPOOL_H__
#define WINPOOL_H__

#include "Python.h"
#include "structmember.h"

typedef struct {
  PyObject_HEAD

  WSAPOLLFD    fdarray[65536];
  ULONG        nfds;

} WinPool;

/* Methods */

PyObject *WinPool_new(PyTypeObject *type, PyObject *args, PyObject *kwds);
int WinPool_init(WinPool *self, PyObject *args, PyObject *kwds);
void WinPool_dealloc(WinPool* self);

PyObject *WinPool_register(WinPool *self, PyObject *args);
PyObject *WinPool_modify(WinPool *self, PyObject *args);
PyObject *WinPool_poll(WinPool *self, PyObject *args);
PyObject *WinPool_dump(WinPool *self, PyObject *args);

/* Structures */

static PyMethodDef WinPool_methods[] = {
  {
    "register", (PyCFunction)WinPool_register, METH_VARARGS,
    "Register FileDescriptior for polling"
  },
  {
    "modify", (PyCFunction)WinPool_modify, METH_VARARGS,
    "Modify FileDescriptior for polling"
  },
  {
    "poll", (PyCFunction)WinPool_poll, METH_VARARGS,
    "Polling"
  },
  {
    "dump", (PyCFunction)WinPool_dump, METH_VARARGS,
    "Dump poll"
  },

  {NULL}  /* Sentinel */

};

static PyMemberDef WinPool_members[] = {
//  {
//    "number", T_INT, offsetof(Noddy, number), 0,
//    "noddy number"
//  },

  {NULL}  /* Sentinel */

};

static PyGetSetDef WinPool_getseters[] = {
//  {
//    "first",
//    (getter)Noddy_getfirst,(setter)Noddy_setfirst,
//    "first name",
//    NULL
//  },
//  {
//    "last",
//    (getter)Noddy_getlast, (setter)Noddy_setlast,
//    "last name",
//    NULL
//  },

  {NULL}  /* Sentinel */

};

/* Main structure */

PyTypeObject WinPoolType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "cPool.WinPool",                            /* tp_name */
  sizeof(WinPool),                            /* tp_basicsize */
  0,                                          /* tp_itemsize */
  (destructor)WinPool_dealloc,                /* tp_dealloc */
  0,                                          /* tp_print */
  0,                                          /* tp_getattr */
  0,                                          /* tp_setattr */
  0,                                          /* tp_reserved */
  0,                                          /* tp_repr */
  0,                                          /* tp_as_number */
  0,                                          /* tp_as_sequence */
  0,                                          /* tp_as_mapping */
  0,                                          /* tp_hash  */
  0,                                          /* tp_call */
  0,                                          /* tp_str */
  0,                                          /* tp_getattro */
  0,                                          /* tp_setattro */
  0,                                          /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,   /* tp_flags     */
  "WinPool objects",                          /* tp_doc */
  0,                                        /* tp_traverse */
  0,                         /* tp_clear */
  0,                         /* tp_richcompare */
  0,                         /* tp_weaklistoffset */
  0,                         /* tp_iter */
  0,                         /* tp_iternext */
  WinPool_methods,             /* tp_methods */
  WinPool_members,             /* tp_members */
  WinPool_getseters,           /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  (initproc)WinPool_init,      /* tp_init */
  0,                         /* tp_alloc */
  WinPool_new,                 /* tp_new */

};

#endif /* WINPOOL_H__ */
