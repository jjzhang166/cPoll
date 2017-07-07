#!/usr/bin/python3

from socket import socket

from cPool import WinPool, EVENT_READ, EVENT_WRITE

s = socket()
fd = s.fileno()
print(fd)

p = WinPool()
p.register(fd, EVENT_READ | EVENT_WRITE)
