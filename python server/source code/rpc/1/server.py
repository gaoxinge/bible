from SimpleXMLRPCServer import SimpleXMLRPCServer

def twice(x):
    return x*x

s = SimpleXMLRPCServer(('', 4242))
s.register_function(twice)
s.serve_forever()