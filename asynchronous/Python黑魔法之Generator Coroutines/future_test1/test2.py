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

h_coroutine = h()
result = None
try:
    g_coroutine = h_coroutine.send(result)
    result = None
except StopIteration as e:
    result = e.value
try:
    f_coroutine = g_coroutine.send(result)
    result = None
except StopIteration as e:
    result = e.value
try:
    f_coroutine.send(result)
    result = None
except StopIteration as e:
    result = e.value
try:
    f_coroutine.send(result)
    result = None
except StopIteration as e:
    result = e.value
try:
    g_coroutine.send(result)
    result = None
except StopIteration as e:
    result = e.value
try:
    h_coroutine.send(result)
    result = None
except StopIteration as e:
    result = e.value