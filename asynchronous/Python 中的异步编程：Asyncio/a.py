async def f():
    print(12345)


async def g():
    await f()


async def h():
    await g()


f_coro = f()
try:
    f_coro.send(None)
except StopIteration as e:
    print("stop")


g_coro = g()
try:
    g_coro.send(None)
except StopIteration as e:
    print("stop")


h_coro = h()
try:
    h_coro.send(None)
except StopIteration as e:
    print("stop")