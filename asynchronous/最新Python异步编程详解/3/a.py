import asyncio
import requests
import time


async def wait_download(url):
    response = await requests.get(url)
    print("get {} response complete.".format(url))


async def main():
    start = time.time()
    await asyncio.wait([
        wait_download("http://www.163.com"),
        wait_download("http://www.mi.com"),
        wait_download("http://www.google.com")])
    end = time.time()
    print("Complete in {} seconds".format(end - start))


loop = asyncio.get_event_loop()
loop.run_until_complete(main())
