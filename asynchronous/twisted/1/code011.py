from twisted.internet import reactor
from twisted.internet.defer import Deferred


class ReturnValue(Exception):

    def __init__(self, value):
        self.value = value


def Return(value):
    raise ReturnValue(value)


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
        except ReturnValue as e:
            reactor.callWhenRunning(self.defer.callback, e.value)

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


def sleep(duration):
    d = Deferred()
    reactor.callLater(duration, d.callback, None)
    return d


@coroutine
def f():
    print(4)
    yield sleep(1)
    print(5)
    yield sleep(2)
    print(6)


f()
reactor.run()
