def f(a, b):
    yield
    return a + b

def g(a, b):
    yield
    return a - b

def h():
    x = yield f(1, 2)
    y = yield g(3, 4)
    return x * y

result = None
h_coroutine = h()
f_coroutine = h_coroutine.send(None)
f_coroutine.send(None)
try:
    f_coroutine.send(None)
except StopIteration as e:
    result = e.value
g_coroutine = h_coroutine.send(result)
g_coroutine.send(None)
try:
    g_coroutine.send(None)
except StopIteration as e:
    result = e.value
try:
    h_coroutine.send(result)
except StopIteration as e:
    result = e.value
print(result)