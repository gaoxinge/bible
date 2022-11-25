import asyncio
import random


async def produce(queue, n):
    for x in range(1, n):
        print('producing {}/{}'.format(x, n))
        await asyncio.sleep(random.random())
        item = str(x)
        await queue.put(item)


async def consume(queue):
    while True:
        item = await queue.get()
        print('consuming item {}...'.format(item))
        await asyncio.sleep(random.random())
        queue.task_done()


async def run(n):
    queue = asyncio.Queue()
    consumer = asyncio.ensure_future(consume(queue))
    await produce(queue, n)
    await queue.join()
    consumer.cancel()


loop = asyncio.get_event_loop()
loop.run_until_complete(run(10))
loop.close()
