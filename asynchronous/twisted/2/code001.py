from twisted.web.server import Site
from twisted.web.static import File
from twisted.internet import reactor

resource = File('D:\\Go\\')
factory = Site(resource)
reactor.listenTCP(8888, factory)
reactor.run()
