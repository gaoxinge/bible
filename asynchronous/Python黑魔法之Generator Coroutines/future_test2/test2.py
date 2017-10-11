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

h_coroutine = h()
result = None
try:
    f_coroutine = h_coroutine.send(result)
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
    g_coroutine = h_coroutine.send(result)
    result = None
except StopIteration as e:
    result = e.value
try:
    g_coroutine.send(result)
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
print(result)
