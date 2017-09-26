def count(f):
    def counted(*args):
        counted.call_count += 1
        return f(*args)
    counted.call_count = 0
    return counted

class count(object):
    
    def __init__(self, f):
        self.f = f
        self.call_count = 0
        
    def __call__(self, *args):
        self.call_count += 1
        return self.f(*args)

class count(object):
    
    call_count = 0
    
    def __init__(self, f):
        self.f = f
        
    def __call__(self, *args):
        count.call_count += 1
        return self.f(*args)
        
def fib(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    return fib(n-2) + fib(n-1)
    
fib = count(fib)
print fib(9)
print fib.call_count