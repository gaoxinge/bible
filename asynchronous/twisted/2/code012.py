from twisted.web.server import Site
from twisted.web.wsgi import WSGIResource
from twisted.internet import reactor


def application(environ, start_response):
    start_response('200 OK', [('Content-type', 'text/plain')])
    return ['Hello World!']


root = WSGIResource(reactor, reactor.getThreadPool(), application)
factory = Site(root)
reactor.listenTCP(8888, factory)
reactor.run()
