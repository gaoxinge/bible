def bottom():
    result = yield 42
    return result
    # return (yield 42)


def middle():
    result = yield from bottom()
    return result
    # return (yield from bottom())


def top():
    result = yield from middle()
    return result
    # return (yield from middle())


gen = top()

value = gen.send(None)
print(value)

try:
    value = gen.send(43)
except StopIteration as e:
    value = e.value
print(value)
