# -*- coding: utf-8 -*-
import functools


class Future(object):
    pass


class _NullFuture(object):

    def result(self):
        return None

    def done(self):
        return True

moment = _NullFuture()


def coroutine(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        future = Future()
        result = func(*args, **kwargs)
        yielded = next(result)
        Runner(result, future, yielded)
        return future
    return wrapper


class Runner(object):

    def __init__(self, gen, result_future, first_yielded):
        self.io_loop = IOLoop.current()
        self.gen = gen
        self.result_future = result_future
        self.future = None
        self.handle_yield(first_yielded)

    def handle_yield(self, yielded):
        self.future = yielded
        if self.future is moment:
            self.io_loop.add_callback(self.run)

    def run(self):
        future = self.future
        if not future.done():
            return
        self.future = None

        try:
            yielded = next(self.gen)
        except StopIteration:
            return

        self.handle_yield(yielded)


class _IOLoop(object):

    def __init__(self):
        self._callbacks = []

    def add_callback(self, callback):
        self._callbacks.append(callback)

    def start(self):
        while self._callbacks:
            callback = self._callbacks.pop(0)
            callback()


class IOLoop(object):

    instance = None

    @staticmethod
    def current():
        if IOLoop.instance is not None:
            return IOLoop.instance

        io_loop = _IOLoop()
        IOLoop.instance = io_loop
        return io_loop


@coroutine
def task1():
    print("task1", 1)
    yield moment
    print("task1", 2)
    yield moment
    print("task1", 3)


@coroutine
def task2():
    print("task2", 1)
    yield moment
    print("task2", 2)


if __name__ == "__main__":
    t1 = task1()
    t2 = task2()
    IOLoop.current().start()