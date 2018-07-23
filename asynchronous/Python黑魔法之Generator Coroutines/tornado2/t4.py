# -*- coding: utf-8 -*-
import functools
import time


class Future(object):

    def __init__(self):
        self._done = False
        self._result = None
        self._callbacks = []

    def done(self):
        return self._done

    def add_done_callback(self, fn):
        self._callbacks.append(fn)

    def set_result(self, result):
        self._result = result
        self._set_done()

    def _set_done(self):
        self._done = True
        if self._callbacks:
            loop = IOLoop.current()
            for cb in self._callbacks:
                loop.add_callback(cb)
            self._callbacks = None

    def result(self):
        return self._result


class _NullFuture(object):

    def result(self):
        return None

    def done(self):
        return True

moment = _NullFuture()


class Return(Exception):

    def __init__(self, value=None):
        self.value = value


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
        # in task2, sleep's future add task2's run to callback
        # in task2, task1's future add task2's run to callback
        elif not self.future.done():
            self.future.add_done_callback(self.run)

    def run(self):
        future = self.future
        if not future.done():
            return
        self.future = None
        value = future.result()

        try:
            yielded = self.gen.send(value)
        except StopIteration:
            self.result_future.set_result(None)
            return
        except Return, e:
            self.result_future.set_result(e.value)  # in task1, task1 add task2's run to io_loop from its future
            return

        self.handle_yield(yielded)


class _IOLoop(object):

    def __init__(self):
        self._callbacks = []
        self._timeouts = []

    def add_timeout(self, deadline, callback):
        self._timeouts.append((deadline, callback))

    def remove_timeout(self, timeout):
        self._timeouts.remove(timeout)

    def add_callback(self, callback):
        self._callbacks.append(callback)

    def start(self):
        while True:
            due_timeouts = []
            for timeout in self._timeouts:
                if time.time() > timeout[0]:
                    due_timeouts.append(timeout)

            while self._callbacks:
                callback = self._callbacks.pop(0)
                callback()

            for timeout in due_timeouts:
                self._timeouts.remove(timeout)
                callback = timeout[1]
                callback()  # in io_loop, io_loop add task2's run to io_loop from sleep's future


class IOLoop(object):

    instance = None

    @staticmethod
    def current():
        if IOLoop.instance is not None:
            return IOLoop.instance

        io_loop = _IOLoop()
        IOLoop.instance = io_loop
        return io_loop


def sleep(duration):
    future = Future()
    io_loop = IOLoop.current()
    io_loop.add_timeout(time.time() + duration, lambda: future.set_result(None))
    print("sleep %ss" % duration)
    return future


@coroutine
def task1():
    print("task1", 1)
    yield moment
    print("task1", 2)
    yield moment
    print("task1", 3)
    raise Return("task1 stop")


@coroutine
def task2():
    print("task2", 1)
    yield sleep(3)
    r = yield task1()
    print(r)
    yield sleep(3)
    print("task2", 2)


if __name__ == "__main__":
    # t1 = task1()
    t2 = task2()
    IOLoop.current().start()