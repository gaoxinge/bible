def count(f):
    def counted(*args):
        counted.call_count += 1
        return f(*args)
    counted.call_count = 0
    return counted    
    
def memo(f):
    def memoized(n):
        if n not in cache:
            cache[n] = f(n)
        return cache[n]
    cache = {}
    return memoized
    
def fib(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    return fib(n-2) + fib(n-1)

m = memo(fib)
fib = count(m)
print fib(9)
print fib.call_count