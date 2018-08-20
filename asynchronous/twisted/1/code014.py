from twisted.internet import reactor
from twisted.internet.defer import Deferred


class Task:

    def __init__(self, gen):
        self._gen = gen
        reactor.callWhenRunning(self.step)

    def step(self, value=None):
        try:
            defer = self._gen.send(value)
            defer.addCallback(self._wakeup)
        except StopIteration as e:
            pass

    def _wakeup(self, result):
        self.step(result)


def moment():
    d = Deferred()
    reactor.callWhenRunning(d.callback, None)
    return d


def f():
    print(4)
    yield moment()
    print(5)
    yield moment()
    print(6)
    return 123


def g():
    print("task f start")
    result = yield from f()
    print("task f finish with result", result)

    print("task g start")
    print(123)
    yield moment()
    print(234)
    yield moment()
    print("task g finish")


Task(g())
reactor.run()
