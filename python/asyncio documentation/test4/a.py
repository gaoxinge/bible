import asyncio

def compute_pi(digits):
    return 3.14

async def main(loop):
    digits = await loop.run_in_executor(None, compute_pi, 2000)
    print('pi: %s' % digits)

loop = asyncio.get_event_loop()
loop.run_until_complete(main(loop))
loop.close()