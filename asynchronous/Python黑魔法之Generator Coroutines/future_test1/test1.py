def f(a, b):
    yield
    return a + b

def g(c):
    d = yield f(1, 2)
    print(d)
    return c - d

def h():
    e = yield g(7)
    print(e)

result = None
h_coroutine = h()
g_coroutine = h_coroutine.send(None)
f_coroutine = g_coroutine.send(None)
f_coroutine.send(None)
try:
    f_coroutine.send(None)
except StopIteration as e:
    result = e.value
try:
    g_coroutine.send(result)
except StopIteration as e:
    result = e.value
try:
    h_coroutine.send(result)
except StopIteration as e:
    pass