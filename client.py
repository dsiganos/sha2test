#!/usr/bin/env python
import socket
import binascii
import sys

md = sys.argv[1]

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 12345))
s.sendall(md)
s.sendall('hello')
s.shutdown(socket.SHUT_WR)
print binascii.hexlify(s.recv(1000))
