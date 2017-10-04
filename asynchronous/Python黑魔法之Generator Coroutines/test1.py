######################
# g call f:          #
# g use next         #
# f doesn't use next #
######################

def f(x, y):
    """callee"""
    yield x - y
    return x + y

def g():
    """caller"""
    f(1, 2)
    yield f(1, 2)

a = g()
print(next(a))
print(next(a))