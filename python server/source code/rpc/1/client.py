from xmlrpclib import ServerProxy

s = ServerProxy('http://localhost:4242')
print s.twice(2)