def patch_future(cls):
    def __iter__(self):
        if not self.done():
            yield self
        return self.result()
    cls.__iter__ = __iter__

from concurrent.futures import Future
patch_future(Future)


from concurrent.futures import ThreadPoolExecutor
import time
import inspect


class Task:

    def __init__(self, gen):
        self._gen = gen

    def step(self, value=None, exc=None):
        try:
            if exc:
                fut = self._gen.throw(exc)
            else:
                fut = self._gen.send(value)
            fut.add_done_callback(self._wakeup)
        except StopIteration as e:
            pass

    def _wakeup(self, fut):
        try:
            result = fut.result()
            self.step(result, None)
        except Exception as exc:
            self.step(None, exc)


def inlined_future(func):
    assert inspect.isgeneratorfunction(func)
    return func


def func(x, y):
    time.sleep(1)
    return x + y


@inlined_future
def do_func(x, y):
    result = yield pool.submit(func, x, y)
    print('Got: ', result)


@inlined_future
def after(delay, gen):
    yield pool.submit(time.sleep, delay)
    yield from gen


pool = ThreadPoolExecutor(max_workers=8)
Task(after(10, do_func(2, 3))).step()
