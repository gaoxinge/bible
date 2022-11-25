from twisted.web.server import Site
from twisted.web.resource import Resource
from twisted.internet import reactor
from twisted.web.static import File
# from twisted.web.error import NoResource
from calendar import calendar


class YearPage(Resource):

    def __init__(self, year):
        Resource.__init__(self)
        self.year = year

    def render_GET(self, request):
        return "<html><body>%s</body></html>" % calendar(self.year)


class NoResource(Resource):

    def render_GET(self, request):
        return "<html><body>fuck</body></html>"


class Calendar(Resource):

    def getChild(self, name, request):
        try:
            year = int(name)
        except ValueError:
            return NoResource()
        return YearPage(year)


# root = YearPage(2018)
root = Calendar()
factory = Site(root)
reactor.listenTCP(8888, factory)
reactor.run()