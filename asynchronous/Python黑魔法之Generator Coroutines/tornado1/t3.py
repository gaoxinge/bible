# -*- coding: utf-8 -*-
from tornado.gen import coroutine, moment, Return
from tornado.ioloop import IOLoop


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
    r = yield task1()
    print(r)
    print("task2", 2)


if __name__ == "__main__":
    # t1 = task1()
    t2 = task2()
    IOLoop.current().start()