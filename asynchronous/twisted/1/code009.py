from twisted.internet import reactor
from twisted.internet.defer import Deferred


class Task:

    def __init__(self, gen, defer):
        self._gen = gen
        self.defer = defer
        reactor.callWhenRunning(self.step)

    def step(self, value=None):
        try:
            defer = self._gen.send(value)
            defer.addCallback(self._wakeup)
        except StopIteration as e:
            reactor.callWhenRunning(self.defer.callback, None)

    def _wakeup(self, result):
        self.step(result)


def coroutine(func):
    def wrapper(*args, **kwargs):
        defer = Deferred()
        gen = func(*args, **kwargs)
        Task(gen, defer)
        return defer
    return wrapper


def moment():
    d = Deferred()
    reactor.callWhenRunning(d.callback, None)
    return d


@coroutine
def f():
    print(4)
    yield moment()
    print(5)
    yield moment()
    print(6)


@coroutine
def g():
    print("task f start")
    yield f()
    print("task f finish")

    print("task g start")
    print(123)
    yield moment()
    print(234)
    yield moment()
    print("task g finish")


g()
reactor.run()
