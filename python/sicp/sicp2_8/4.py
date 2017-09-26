def count(f):
    def counted(*args):
        counted.call_count += 1
        return f(*args)
    counted.call_count = 0
    return counted 
    
cache = {}
def fib_m(n):

    if n not in cache:
        if n == 0:
            cache[0] = 0
        elif n == 1:
            cache[1] = 1
        else:
            cache[n] = fib_m(n-2) + fib_m(n-1)
    
    return cache[n]
    
fib_m = count(fib_m)
print fib_m(9)
print fib_m.call_count