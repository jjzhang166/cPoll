
#include <stdio.h>

#ifdef _WIN32
#include <WinSock2.h>
#include <windows.h>
#endif

#include "Python.h"

#include "cPool.h"

#ifdef _WIN32
PyTypeObject WinPoolType;
#endif

void PyComplete_cPool(void *m)
{
  fprintf(stderr, "Complete %p\n", m);
 
#ifdef _WIN32
  WSACleanup();
#endif /* _WIN32 */
}

PyObject* PyInit_cPool(void)
{
  PyObject* m;

#ifdef _WIN32
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;

  /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
  wVersionRequested = MAKEWORD(2, 2);

  err = WSAStartup(wVersionRequested, &wsaData);
  if (err != 0) {
    return NULL;
  }
#endif /* _WIN32 */

#ifdef _WIN32
  if (PyType_Ready(&WinPoolType) < 0) {
    return NULL;
  }
#endif

  m = PyModule_Create(&cPoolModule);
  fprintf(stderr, "Init %p\n", m);
  if (m == NULL) {
    return NULL;
  }

#ifdef _WIN32
  Py_INCREF(&WinPoolType);
  PyModule_AddObject(m, "WinPool", (PyObject *)&WinPoolType);
#endif

  /* Constants */

  PyModule_AddIntConstant(m, "EVENT_READ", POLLIN );
  PyModule_AddIntConstant(m, "EVENT_WRITE", POLLOUT );
  PyModule_AddIntConstant(m, "EVENT_DISCONNECT", POLLERR | POLLHUP | POLLNVAL );

  return m;
}
