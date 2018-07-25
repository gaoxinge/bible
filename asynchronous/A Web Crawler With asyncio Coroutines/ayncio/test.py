import aiohttp
import asyncio

try:
    from asyncio import JoinableQueue as Queue
except ImportError:
    from asyncio import Queue


class Crawler:

    def __init__(self, root_url, max_redirect):
        self.max_tasks = 10
        self.max_redirect = max_redirect
        self.q = Queue()
        self.seen_urls = set()

        self.session = aiohttp.ClientSession(loop=loop)

        self.q.put((root_url, self.max_redirect))

    @asyncio.coroutine
    def crawl(self):
        workers = [asyncio.Task(self.work()) for _ in range(self.max_tasks)]
        yield from self.q.join()
        for w in workers:
            w.cancel()

    @asyncio.coroutine
    def work(self):
        while True:
            url, max_direct = yield from self.q.get()
            yield from self.fetch(url, max_redirect)
            self.q.task_done()  # 多线程：https://segmentfault.com/q/1010000009765115

    @asyncio.coroutine
    def fetch(self, url, max_redirect):
        response = yield from self.session.get(url, allow_redirects=False)

        try:
            if is_redirect(response):
                if max_redirect > 0:
                    next_url = response.headers['location']
                    if next_url in self.seen_urls:
                        return
                    self.seen_urls.add(next_url)
                    self.q.put_nowait((next_url, max_redirect - 1))
            else:
                links = yield from self.parse_links(response)
                for link in links.differenct(self.seen_urls):
                    self.q.put_nowait((link, self.max_redirect))
                self.seen_urls.update(links)
        finally:
            yield from response.release()


loop = asyncio.get_event_loop()
crawler = Crawler('http://xkcd.com', max_redirect=10)
loop.run_until_complete(crawler.crawl())
