from twisted.web.server import Site
from twisted.web.resource import Resource
from twisted.internet import reactor
from twisted.web.static import File
from calendar import calendar


class YearPage(Resource):
    # isLeaf = True

    def __init__(self, year):
        Resource.__init__(self)
        self.year = year

    def render_GET(self, request):
        return "<html><body>%s</body></html>" % calendar(self.year)


class Calendar(Resource):

    def getChild(self, name, request):
        return YearPage(int(name))


# root = YearPage(2018)
root = Calendar()
factory = Site(root)
reactor.listenTCP(8888, factory)
reactor.run()