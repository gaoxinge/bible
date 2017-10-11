from types import GeneratorType

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

coroutine = h()
future = []
result = None
while True:
    try:
        next_coroutine = coroutine.send(result)
        if isinstance(next_coroutine, GeneratorType):
            future.append(coroutine)
            coroutine = next_coroutine
        result = None
    except StopIteration as e:
        if future:
            coroutine = future.pop()
        else:
            break
        result = e.value