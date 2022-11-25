import asyncio
import aiohttp
import time


async def download(url):
    print("get: %s" % url)
    async with aiohttp.ClientSession() as session:
        async with session.get(url) as resp:
            print(resp.status)


async def main():
    start = time.time()
    await asyncio.wait([
        download("http://www.163.com"),
        download("http://www.mi.com"),
        download("http://www.baidu.com")])
    end = time.time()
    print("Complete in {} seconds".format(end - start))


loop = asyncio.get_event_loop()
loop.run_until_complete(main())
