from types import coroutine
import asyncio


@coroutine
def f():
    return 123


@asyncio.coroutine
def g():
    return 123


f_coro = f()
print(f_coro)


g_coro = g()
try:
    g_coro.send(None)
except Exception as e:
    print(e.value)