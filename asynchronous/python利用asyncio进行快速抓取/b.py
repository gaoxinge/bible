import asyncio


@asyncio.coroutine
def moment():
    yield
    return


@asyncio.coroutine
def f(a):
    print(a)
    yield from moment()
    print(a)
    yield from moment()
    print(a)


@asyncio.coroutine
def g(b):
    print(b)
    yield from f(b - 1)
    print(b)
    yield from f(b - 1)
    print(b)


loop = asyncio.get_event_loop()
loop.create_task(f(456))
loop.create_task(g(123))
loop.run_forever()

# 两个任务交替
# 两种看法：
# - 把f插入到g中，切换点在yield from moment
# - 把f看作g的子任务:
#     - yield from f：suspend g，start f
#     - f run：运行到yield from moment
#    - finish f：stop f, restart g
