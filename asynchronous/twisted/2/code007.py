from twisted.web.server import Site
from twisted.web.resource import Resource
from twisted.internet import reactor
import cgi


class FormPage(Resource):

    def render_GET(self, request):
        return '<html><body><form method="POST"><input name="the-field" type="text" /></form></body></html>'

    def render_POST(self, request):
        return '<html><body>You submitted: %s</body></html>' % (cgi.escape(request.args["the-field"][0]),)

root = Resource()
root.putChild("form", FormPage())
factory = Site(root)
reactor.listenTCP(8888, factory)
reactor.run()
