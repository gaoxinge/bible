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
def g(c):
    d = yield f(1, 2)
    print(d)
    return c - d

@Future
def h():
    e = yield g(7)
    print(e)

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
        if future.fut:
            future = future.fut
        else:
            break
        result = e.value