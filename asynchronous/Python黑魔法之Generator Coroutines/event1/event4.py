# -*- coding: utf-8 -*-
from functools import wraps
from abc import ABCMeta, abstractmethod
from time import time


class Future(object):

    def __init__(self):
        self.callback = lambda: None

    def set_callback(self, callback):
        self.callback = callback

    def done(self):
        self.callback()


class Event(object):

    __metaclass__ = ABCMeta

    def __init__(self, *args, **kwargs):
        self.callback = None

    def set_callback(self, callback):
        self.callback = callback

    def done(self):
        self.callback()

    @abstractmethod
    def is_ready(self):
        pass


class _sleep(Event):

    def __init__(self, timeout):
        self.timeout = timeout
        self.start_time = time()

    def is_ready(self):
        return time() - self.start_time >= self.timeout


def sleep(timeout):
    future = Future()
    event = _sleep(timeout)
    event.set_callback(lambda: future.done())
    events.append(event)
    return future


def select(events):
    ready_events = []
    for event in events:
        if event.is_ready():
            ready_events.append(event)
    return ready_events


events = []


def run():
    while events:
        ready_events = select(events)
        for event in ready_events:
            events.remove(event)
            event.done()


def _next(gen, future):
    try:
        yield_future = next(gen)
        yield_future.set_callback(lambda: _next(gen, future))
    except StopIteration:
        future.done()


def coroutine(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        future = Future()
        gen = func(*args, **kwargs)
        _next(gen, future)
        return future
    return wrapper


@coroutine
def task(name):
    print(name, 1)
    yield sleep(1)
    print(name, 2)
    yield sleep(2)
    print(name, 3)


@coroutine
def task2(name):
    print(name, "task2")
    yield task(name)
    print(name, "task2")


tasks = [task2("abc")]
run()
