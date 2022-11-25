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
    yield from asyncio.sleep(1)
    print(a)


loop = asyncio.get_event_loop()
loop.create_task(f(123))
loop.create_task(f(1234))
loop.run_forever()


# coroutine, yield
# asyncio.coroutine, yield from
# async, await
