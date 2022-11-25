def decorator(func):
    def wrapper(*args, **kwargs):
        print("I am decorator")
        ret = func(*args, **kwargs)
        return ret
    return wrapper
    
    
@decorator
def hello(str):
    print("Hello {0}".format(str))
    

@decorator
def add(a, b):
    print("add %d + %d = %d" % (a, b, a + b))
    return a + b
    
    
print hello("KerKer")
print add(1, 2)