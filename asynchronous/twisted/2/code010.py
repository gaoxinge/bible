from twisted.web.server import Site, NOT_DONE_YET
from twisted.web.resource import Resource
from twisted.internet import reactor
from twisted.internet.task import deferLater


# first consume 5, second consume 5 s
class DelayedResource(Resource):

    def _delayRender(self, request):
        request.write("<html><body>Sorry to keep you waiting.</body></html>")
        request.finish()

    def _responseFailed(self, err, call):
        print(1234)
        call.cancel()

    def render_GET(self, request):
        call = reactor.callLater(5, self._delayRender, request)
        request.notifyFinish().addErrback(self._responseFailed, call)
        return NOT_DONE_YET


root = Resource()
root.putChild("x", DelayedResource())
factory = Site(root)
reactor.listenTCP(8888, factory)
reactor.run()
