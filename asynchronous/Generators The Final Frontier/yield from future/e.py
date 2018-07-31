from concurrent.futures import Future
from concurrent.futures import ThreadPoolExecutor
import time
import inspect


class Task(Future):

    def __init__(self, gen):
        super().__init__()
        self._gen = gen

    def step(self, value=None, exc=None):
        try:
            if exc:
                fut = self._gen.throw(exc)
            else:
                fut = self._gen.send(value)
            fut.add_done_callback(self._wakeup)
        except StopIteration as exc:
            self.set_result(exc.value)

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
    time.sleep(10)
    return x + y


@inlined_future
def do_func(x, y):
    result = yield pool.submit(func, x, y)
    print('Got: ', result)
    return result


pool = ThreadPoolExecutor(max_workers=8)
t = Task(do_func(2, 3))
t.step()
print(t.result())
