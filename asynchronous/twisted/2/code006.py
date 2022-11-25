from twisted.web.server import Site
from twisted.web.resource import Resource
from twisted.internet import reactor


class PaymentRequired(Resource):
    
    def render_GET(self, request):
        request.setResponseCode(402)
        return "<html><body>Please swipe your credit card</body></html>"

root = Resource()
root.putChild("buy", PaymentRequired())
factory = Site(root)
reactor.listenTCP(8888, factory)
reactor.run()
