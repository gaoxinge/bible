def f():
    yield 1
    yield 2
    yield 3
    return 4


def g():
    result = yield from f()
    return result


g_coro = g()
print(g_coro.send(None))
print(g_coro.send(None))
print(g_coro.send(None))
try:
    g_coro.send(None)
except StopIteration as ex:
    print(ex.value)


class A:

    def __init__(self, l):
        self.l = l
        self.index = 0

    def __iter__(self):
        for _ in self.l:
            yield _
        return "finish"


def g():
    result = yield from A([1, 2, 3])
    return result

g_coro = g()
print(g_coro.send(None))
print(g_coro.send(None))
print(g_coro.send(None))
try:
    g_coro.send(None)
except StopIteration as ex:
    print(ex.value)
