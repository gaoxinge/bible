from twisted.web.server import Site
from twisted.web.resource import Resource
from twisted.internet import reactor
from twisted.web.static import File

root = Resource()
root.putChild("foo", File("D:\\Go\\"))
root.putChild("bar", File("D:\\GoPath\\"))
root.putChild("baz", File("D:\\GoLand 2018.1.2\\"))

factory = Site(root)
reactor.listenTCP(8888, factory)
reactor.run()