from concurrent.futures import ThreadPoolExecutor


class Task:

    def __init__(self, gen):
        self._gen = gen

    def step(self, value=None):
        try:
            fut = self._gen.send(value)
            fut.add_done_callback(self._wakeup)
        except StopIteration as e:
            pass

    def _wakeup(self, fut):
        result = fut.result()
        self.step(result)


def func(x, y):
    import time
    time.sleep(1)
    return x + y


def do_many(n):
    while n > 0:
        result = yield pool.submit(func, n, n)
        print('Got: ', result)
        n -= 1


pool = ThreadPoolExecutor(max_workers=8)
t = Task(do_many(10))
t.step()
