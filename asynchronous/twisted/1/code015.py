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


def sleep(duration):
    d = Deferred()
    reactor.callLater(duration, d.callback, None)
    return d


def f():
    print(4)
    yield sleep(1)
    print(5)
    yield sleep(2)
    print(6)
    return 123


Task(f())
reactor.run()
