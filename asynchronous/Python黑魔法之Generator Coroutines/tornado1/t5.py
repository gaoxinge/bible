# -*- coding: utf-8 -*-
from tornado.concurrent import Future
from tornado.gen import coroutine, moment, Return
from tornado.ioloop import IOLoop


def sleep(duration):
    future = Future()
    io_loop = IOLoop.current()
    io_loop.add_timeout(io_loop.time() + duration, lambda: future.set_result(None))
    print("sleep %ss" % duration)
    return future


def sleep_compute(duration, a, b):
    future = Future()
    io_loop = IOLoop.current()
    io_loop.add_timeout(io_loop.time() + duration, lambda: future.set_result(a + b))
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
    r = yield sleep_compute(3, 1, 2)
    print(r)
    print("task2", 2)


if __name__ == "__main__":
    # t1 = task1()
    t2 = task2()
    IOLoop.current().start()