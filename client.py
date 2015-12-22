#!/usr/bin/env python
import socket
import binascii
import sys
import hashlib

md = sys.argv[1]

# connect to peer
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 12345))

# algorithm name
s.sendall(md)
h = hashlib.new(md)

# read data from stdin and process
data = sys.stdin.read(1000)
while len(data) > 0:
    s.sendall(data)
    h.update(data)
    data = sys.stdin.read(1000)

# signal end of data
s.shutdown(socket.SHUT_WR)

# read response/hash
response = s.recv(1000)

# calculate local hash
localhash = h.digest()

# print result
print binascii.hexlify(response)
print binascii.hexlify(localhash)
if response == localhash:
    print "PASS"
    sys.exit(0)
else:
    print "****** FAIL ******"
    sys.exit(1)
