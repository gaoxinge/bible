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
    print 4
    yield moment()
    print 5
    yield moment()
    print 6


Task(f())
reactor.run()
