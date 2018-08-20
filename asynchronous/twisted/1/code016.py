def f():
    yield 1
    yield 2
    return 123


def g():
    result = yield from f()
    print(result)


coro = g()
while True:
    try:
        coro.send(None)
    except StopIteration as e:
        break
