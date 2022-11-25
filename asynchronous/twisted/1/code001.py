from twisted.internet import reactor


def f(a):
    print a


reactor.callWhenRunning(f, 1)
reactor.callLater(2, f, 2)
reactor.run()