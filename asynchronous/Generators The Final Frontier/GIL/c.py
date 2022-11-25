def patch_future(cls):
    def __iter__(self):
        result = yield self
        return result
    cls.__iter__ = __iter__

from concurrent.futures import Future
patch_future(Future)


from concurrent.futures import ProcessPoolExecutor
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


def start_inline_future(fut):
    """no block"""
    t = Task(fut)
    t.step()
    return t


def run_inline_future(fut):
    """block"""
    t = start_line_future(fut)
    return t.result()


def fib(n):
    return 1 if n <= 2 else (fib(n-1) + fib(n-2))


@inlined_future
def compute_fibs(n):
    result = []
    for i in range(n):
        val = yield from pool.submit(fib, i)
        result.append(val)
    return result


if __name__ == "__main__":
    start = time.time()
    pool = ProcessPoolExecutor(4)
    t1 = start_inline_future(compute_fibs(35))  # non_block
    t2 = start_inline_future(compute_fibs(35))
    print(t1.result())
    print(t2.result())
    print(time.time() - start)
