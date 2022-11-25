from twisted.web.server import Site, NOT_DONE_YET
from twisted.web.resource import Resource
from twisted.internet import reactor
import time


# first consume 5, second consume 5 s
class DelayedResource(Resource):

    def _delayRender(self, request):
        request.write("<html><body>Sorry to keep you waiting.</body></html>")
        request.finish()

    def render_GET(self, request):
        reactor.callLater(5, self._delayRender, request)
        return NOT_DONE_YET


# first consume 5 s, second consume 10 s
# class DelayedResource(Resource):
#
#     def render_GET(self, request):
#         time.sleep(5)
#         return "<html><body>Sorry to keep you waiting.</body></html>"

root = Resource()
root.putChild("x", DelayedResource())
factory = Site(root)
reactor.listenTCP(8888, factory)
reactor.run()
