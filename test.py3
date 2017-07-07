#!/usr/bin/python3 -u

from sys import stdout
from socket import socket, AF_INET, SOCK_STREAM

from cPool import WinPool, EVENT_READ, EVENT_WRITE, EVENT_DISCONNECT

class Application(object):
    def __init__(self):
        self._poller = WinPool()
        self._selectable = {}


    def createConnection(self):
        s = socket(AF_INET, SOCK_STREAM)
        s.setblocking(0)
        err = s.connect_ex(('jabber.ru', 5222))
        print(err)
        
        fd = s.fileno()
        print(fd)
        self._poller.register(fd, EVENT_READ | EVENT_WRITE)
        #
        self._selectable[fd] = s


    def run(self):
        # Create brandnew 100 connection
        for _ in range(2):
            self.createConnection()

        # Wait
        i = 0
        while True:
            self._poller.dump()
            #
            v = self._poller.poll(1000)
            stdout.write("Count: {v} Iteration: {i}\r".format(v=v, i=i))
            i += 1
            #
            if v == len(self._selectable):
                print("=== All ===")
                #p.modify(fd, 0)
                for fd, s in self._selectable.items():
                    self._poller.modify(fd, EVENT_READ)


if __name__ == "__main__":
    app = Application()
    app.run()
