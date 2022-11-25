def count_frames(f):
    def counted(*args):
        counted.open_count += 1
        counted.max_count = max(counted.max_count, counted.open_count)
        result = f(*args)
        counted.open_count -=1
        return result
    counted.open_count = 0
    counted.max_count = 0
    return counted
    
def fib(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    return fib(n-2) + fib(n-1)
    
fib = count_frames(fib)
print fib(9)
print fib.open_count
print fib.max_count