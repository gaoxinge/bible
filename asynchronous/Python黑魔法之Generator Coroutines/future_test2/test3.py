from types import GeneratorType

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
        result = e.value
        if future:
            coroutine = future.pop()
        else:
            break
print(result)