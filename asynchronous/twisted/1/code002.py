from twisted.internet import reactor
from twisted.internet.defer import Deferred


def f(a):
    return a


def g(a):
    return sorted(a)


def h(a):
    print a


d = Deferred()
d.addCallback(f)
d.addCallback(g)
d.addCallback(h)
d.callback([3, 2, 1])