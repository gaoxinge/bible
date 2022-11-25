import time

def profile(func):
    def wrapper(*args, **kwargs):
        s = time.time()
        result = func(*args, **kwargs)
        e = time.time()
        print("time:", e-s)
        return result
    return wrapper
    


def fib(n):
    if n < 2:
        return n
    return fib(n-1) + fib(n-2)
    
@profile 
def fib_py(n):
    return fib(n)
    

    
from ctypes import cdll
libfib_dll = cdll.LoadLibrary("fib.dll")

@profile
def fib_dll(n):
    return libfib_dll.fib(n)

    
    
import libfib as libfib_pyd

@profile
def fib_pyd(n):
    return libfib_pyd.fib(n)

    

print fib_py(35)
print fib_dll(35)
print fib_pyd(35)