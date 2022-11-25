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


loop = asyncio.get_event_loop()
loop.create_task(f(123))
loop.create_task(f(456))
loop.run_forever()

# 两个任务交替执行
