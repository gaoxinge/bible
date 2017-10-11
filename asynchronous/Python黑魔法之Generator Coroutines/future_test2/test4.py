class Future:

    def __init__(self, func):
        self.func = func
        self.fut = None

    def __call__(self, *args, **kwargs):
        self.gen = self.func(*args, **kwargs)
        return self

@Future
def f(a, b):
    yield
    return a + b

@Future
def g(a, b):
    yield
    return a - b

@Future
def h():
    x = yield f(1, 2)
    y = yield g(3, 4)
    return x * y

future = h()
result = None
while True:
    try:
        next_future = future.gen.send(result)
        if isinstance(next_future, Future):
            next_future.fut = future
            future = next_future
        result = None
    except StopIteration as e:
        result = e.value
        if future.fut:
            future = future.fut
        else:
            break
print(result)