from twisted.internet import reactor
from twisted.internet.defer import Deferred, inlineCallbacks


def sleep(duration):
    d = Deferred()
    reactor.callLater(duration, d.callback, None)
    return d


@inlineCallbacks
def f():
    print 4
    yield sleep(1)
    print 5
    yield sleep(2)
    print 6


f()
reactor.run()