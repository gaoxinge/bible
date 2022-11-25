# -*- coding: utf-8 -*-
from tornado.gen import coroutine, moment
from tornado.ioloop import IOLoop


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
    yield task1()
    print("task2", 2)


if __name__ == "__main__":
    # t1 = task1()
    t2 = task2()
    IOLoop.current().start()