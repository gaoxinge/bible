import asyncio
import random


async def produce(queue, n):
    for x in range(1, n + 1):
        print('producing {}/{}'.format(x, n))
        await asyncio.sleep(random.random())
        item = str(x)
        await queue.put(item)

    await queue.put(None)


async def consume(queue):
    while True:
        item = await queue.get()
        if item is None:
            break

        print('consuming item {}...'.format(item))
        await asyncio.sleep(random.random())


loop = asyncio.get_event_loop()
queue = asyncio.Queue(loop=loop)
producer_coro = produce(queue, 10)
consumer_coro = consume(queue)
loop.run_until_complete(asyncio.gather(producer_coro, consumer_coro))
loop.close()
