
#include <stdio.h>

#include <WinSock2.h>
#include <windows.h>

#include "Python.h"
#include "structmember.h"

#include "WinPool.h"


void WinPool_dealloc(WinPool* self)
{
//    Py_XDECREF(self->first);
//    Py_XDECREF(self->last);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *WinPool_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  WinPool *self;

  self = (WinPool *)type->tp_alloc(type, 0);
  if (self != NULL) {
    self->nfds = 0;
  }

  return (PyObject *)self;
}

int WinPool_init(WinPool *self, PyObject *args, PyObject *kwds)
{
  return 0;
}

PyObject *WinPool_register(WinPool *self, PyObject *args)
{
  int        fd;
  int        mask;
  WSAPOLLFD *pollfd;

  if (!PyArg_ParseTuple(args, "ii", &fd, &mask)) {
    return -1;
  }

  fprintf(stderr, "register: fd = %d mask = %d\n", fd, mask);

  pollfd = &self->fdarray[self->nfds];
  pollfd->fd = fd;
  pollfd->events = mask;
  pollfd->revents = mask;

  ++self->nfds;

  return Py_BuildValue("i", 0);
}

PyObject *WinPool_modify(WinPool *self, PyObject *args)
{
  int        fd;
  int        mask;
  int        i;
  WSAPOLLFD *pollfd;
  int        rval = 0;

  if (!PyArg_ParseTuple(args, "ii", &fd, &mask)) {
    return -1;
  }

  fprintf(stderr, "modify: fd = %d mask = %d\n", fd, mask);

  for(i=0; i < self->nfds; i++) {
    /* Debug message */
    fprintf(stderr, "modify: i = %d\n", i);
    /* Iteration */
    pollfd = &self->fdarray[i];
    if (pollfd->fd == fd) {
      fprintf(stderr, "modify: ==\n");
      pollfd->events = mask;
      pollfd->revents = 0;
      //
      rval += 1;
    }
  }
  return Py_BuildValue("i", rval);
}


PyObject *WinPool_dump(WinPool *self, PyObject *args)
{
  int i;
  WSAPOLLFD *pollfd;

  if (!PyArg_ParseTuple(args, "")) {
    return -1;
  }

  for(i=0; i < self->nfds; i++) {
    pollfd = &self->fdarray[i];

    fprintf(stderr, " %3d: %d %x %x\n", i, pollfd->fd, pollfd->events, pollfd->revents);
  }

  return Py_BuildValue("");
}


PyObject *WinPool_poll(WinPool *self, PyObject *args)
{
  int         rval;
  INT         timeout = 1000;
  WSAPOLLFD  *pollfd = &self->fdarray;

  if (!PyArg_ParseTuple(args, "|i", &timeout)) {
    return -1;
  }

  rval = WSAPoll(pollfd, self->nfds, timeout);
  if (rval == SOCKET_ERROR) {
    int err;
    /* An error occurred. Call the WSAGetLastError function to retrieve the extended error code. */
    err = WSAGetLastError();
    /* Create Exception message */
    fprintf(stderr, "Error %d\n", err);
    PyErr_SetString(PyExc_TypeError, "An error occurred");
    return NULL;
  }
  
  return Py_BuildValue("i", rval);
}
