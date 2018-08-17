from twisted.internet import reactor
from twisted.internet.defer import Deferred, inlineCallbacks


def moment():
    d = Deferred()
    reactor.callWhenRunning(d.callback, None)
    return d


@inlineCallbacks
def f():
    print 4
    yield moment()
    print 5
    yield moment()
    print 6


f()
reactor.run()