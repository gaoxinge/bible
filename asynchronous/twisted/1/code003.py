from twisted.internet import reactor
from twisted.internet.defer import Deferred


def sleep(duration):
    d = Deferred()
    reactor.callLater(duration, d.callback, None)
    return d


def f(_):
    print 3


d = sleep(5)
d.addCallback(f)
reactor.run()