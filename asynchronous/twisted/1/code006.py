from twisted.internet import reactor
from twisted.internet.defer import Deferred, inlineCallbacks, returnValue


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
    returnValue(123)


@inlineCallbacks
def g():
    print "task f start"
    result = yield f()
    print "task f finish with result", result

    print "task g start"
    print 123
    yield
    print 234
    yield
    print "task g finish"


g()
reactor.run()