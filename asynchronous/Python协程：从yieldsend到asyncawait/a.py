class A:
    """iterator"""

    def __init__(self, l):
        self.l = l
        self._index = 0

    def __next__(self):
        if self._index == len(self.l):
            raise StopIteration
        result = self.l[self._index]
        self._index += 1
        print(result)

a = A([1, 2, 3])
next(a)
next(a)
next(a)


class B:
    """iterable object"""

    def __init__(self, l):
        self.l = l

    def __iter__(self):
        return A(self.l)

b = B([1, 2, 3])

# method 1
a = iter(b)
next(a)
next(a)
next(a)

# method 2
for _ in b:
    pass

# method 3
a = iter(b)
while True:
    try:
        _ = next(a)
    except StopIteration as e:
        break


print("=" * 30)


def f():
    yield from B([1, 2, 3, 4])

f_coro = f()
f_coro.send(None)
f_coro.send(None)
f_coro.send(None)
f_coro.send(None)
try:
    f_coro.send(None)
except StopIteration as e:
    print("stop")


def g():
    b = B([1, 2, 3, 4])
    a = iter(b)
    while True:
        try:
            yield next(a)
        except StopIteration as e:
            break

g_coro = g()
g_coro.send(None)
g_coro.send(None)
g_coro.send(None)
g_coro.send(None)
try:
    g_coro.send(None)
except StopIteration as e:
    print("stop")


# yield from iterable object
# yield from generator
