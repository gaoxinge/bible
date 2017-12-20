## tcp, udp

### 如何运行

```
BaseServer ---> TCPServer --> UDPServer
                   |
                   |
                   v
         UnixStreamServer --> UnixDatagramServer
```

```
ForkingMixIn + TCPServer = ForkingTCPServer
ForkingMixIn + UDPServer = ForkingUDPServer
ThreadingMixIn + TCPServer = ThreadingTCPServer
ThreadingMixIn + UDPServer = ThreadingUDPServer
ThreadingMixIn + UnixStreamServer = ThreadingUnixStreamServer
ThreadingMixIn + UnixDatagramServer = ThreadingUnixDatagramServer
```

```
BaseRequestHandler --> StreamRequestHandler
       |
       |
       v
DatagramRequestHandler
```

- BaseServer
  - 初始化server_address, RequestHandlerClass
  - 运行如下

```
handle_request --|
                 |
server_forever ----> _handle_request_noblock ---> process_request ---> finish_request ---> handle
```

- BaseRequestHandler
  - 初始化request, client_address, server
  - 运行如下

```
setup --> handle --> finish
```

### select

位于handle_request和server_forever里面使用了_eintr_retry，而_eintr_retry只是对select.select进行了包装。若_eintr_retry得到的rlist有self的话，则使用_handle_request_noblock处理，否则handle_timeout或者继续轮询。参考
 
- [select.select](https://docs.python.org/3/library/select.html#select.select)

过程如下：

- handle_request：等待fd_sets直到timeout，若fd_sets[0]（即rlist为空，不包含self），则使用_handle_request_noblock处理
- server_forever：轮询直到r有self，然后使用_handle_request_noblock处理
- _handle_request_noblock：
  - get_requst：由于TCP和UDP获取客户端的方式不同，因此get_request需要在TCPServer和UDPServer中实现
  - process_request
  - shutdown_request

### multiprocess

位于ForkingMixIn，主要重写了process_request。参考

- [os](https://docs.python.org/3/library/os.html)
- [os.fork](https://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/0013868323401155ceb3db1e2044f80b974b469eb06cb43000)
- [os.waitpid](https://www.programcreek.com/python/example/424/os.waitpid)
- [lsbaws-part3](https://ruslanspivak.com/lsbaws-part3/)
- os.waitpid(-1, 0)：阻塞等待任意子进程
- os.waitpid(pid, os.WNOHANG)：非阻塞等待特定子进程。若没有结束状态的子进程，则os.waitpid返回(0, 0)
- os._exit(0)：正常推出
- os._exit(1)：异常退出

过程如下：

- process_request
  - 调用collect_children。由于max_children为可使用的子进程个数，所以需要使用collect_children控制
  - 主进程：初始化active_children，添加子进程pid，用于跟踪检测，关闭子进程的socket副本
  - 子进程：finish_request，并使用os._exit退出
- handle_timeout
  - 调用collect_children。如果不调用collect_children，那么可能主进程结束，但子进程未结束，因此会产生僵尸进程
- collect_children
  - 判断active_children有没有初始化
  - 阻塞等待可用子进程
  - 回收退出的进程：注意此时pid可能为0

其它如下：

- 与lsbaws-part3的区别
  - lsbaws-part3在子进程中关闭了父进程的socket副本
  - lsbaws-part3使用signal.signal注册回调
- 没用windows版本的多进程
  - 因为windows版本的多进程调用函数时，需要序列化函数的参数，那么在socket编程中，需要序列化request，client_address，所以比较麻烦
  - gunicorn也是使用的fork，只支持unix
- collect_children
  - 在处理超时时，需要使用collect_children阻塞回收：此时只有一个子进程，因此可以在collect_children中的阻塞等待可用子进程中回收
  - 在程序退出时，需要使用collect_children阻塞回收：已在最新版的[cpython](https://github.com/python/cpython/blob/master/Lib/socketserver.py#L621)中改掉了

测试如下：

- 不关闭父进程的socket副本

- windows版本
  - 尝试用_subprocess重新写一个Popen：还是要把函数，参数序列化
  - 尝试对socket进行其他种类的序列化：了解序列化

### multithread

位于ThreadingMixIn，主要重写了process_request

- process_request
  - 启动线程，调用process_request_thread
- process_request_thread
  - 调用finish_request

### mixin要放在前面

ForkingMixIn，ThreadingMixIn只重写了process_request，handle_timeout，可以放在后面

### 为什么没有ForkingUnixStreamServer, ForkingUnixDatagramServer

### rfile, wfile

- [What is the difference between StringIO and io.StringIO in Python2.7?](https://stackoverflow.com/questions/3410309/what-is-the-difference-between-stringio-and-io-stringio-in-python2-7)
- [StringIO](https://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/001431918785710e86a1a120ce04925bae155012c7fc71e000)

```python
try:
    from cStringIO import StringIO
except ImportError:
    from StringIO import StringIO
f = StringIO()
f.write('hello')
f.write(' ')
f.write('world')
print f.getvalue()
```

- StreamRequestHandler：
- DatagramRequestHandler：

### python3与python2的区别

python3使用了[selectors](https://docs.python.org/3/library/selectors.html)

## http

### 如何运行

```
BaseHTTPServer: HTTPServer, BaseHTTPRequestHandler
SimpleHTTPServer: SimpleHTTPRequestHandler
CGIHTTPServer: CGIHTTPRequestHandler
```

```
TCPServer --> HTTPServer
```

```
StreamRequestHandler --> BaseHTTPRequestHandler --> SimpleHTTPRequestHandler --> CGIHTTPRequestHandler
```

- BaseHTTPRequestHandler
  - handle --> handle_one_request --> parse_request
  - send_error
  - 处理请求
    - send_response
    - send_header
    - end_headers
- SimpleHTTPRequestHandler
  - do_GET
  - do_HEAD
  - send_head
- CGIHTTPRequestHandler
  - do_POST
  - send_head
  
### BaseHTTPRequestHandler如何运行

- handle调用handle_one_request
- handle_one_request调用以do_开头的，以GET，POST，HEAD，PUT，DELETE结尾的方法

### SimpleHTTPRequestHandler如何运行

- do_GET
- do_HEAD

### CGIHTTPRequestHandler如何运行

- do_POST
  - is_cgi：判断self.path是否对应cgi脚本
  - run_cgi：设置scriptfile，配置环境env。判断系统是unix还是windows
    - unix：fork出子进程，在子进程中执行脚本和环境，返回数据
	- windows：subprocess执行脚本和环境，返回数据
	
### unix是否阻塞

- 主进程通过os.waitpid(pid, 0)阻塞
- 没有使用subprocess

### windows是否阻塞

- 使用subprocess阻塞

### rfile, wfile

- 与客户端一一对应
- 与服务端没有对应关系

## rpc

- [XML-RPC Specification](http://xmlrpc.scripting.com/spec.html)
- [python项目实践八：使用XML-RPC进行远程文件共享](http://www.code123.cc/1335.html)

### 如何运行

- SimpleXMLRPCServer
  - SimpleXMLRPCDispatcher
  - SimpleXMLRPCRequestHandler(BaseHTTPRequestHandler)
  - SimpleXMLRPCServer(TCPServer, SimpleXMLRPCDispatcher)
  - MultiPathXMLRPCServer(SimpleXMLRPCServer)
  - CGIXMLRPCRequestHandler(SimpleXMLRPCDispatcher)
- DocXMLRPCServer
  - ServerHTMLDoc(HTMLDoc)
  - XMLRPCDocGenerator
  - DocXMLRPCRequestHandler(SimpleXMLRPCRequestHandler)
  - DocXMLRPCServer(SimpleXMLRPCServer, XMLRPCDocGenerator)
  - DocCGIXMLRPCRequestHandler(CGIXMLRPCRequestHandler, XMLRPCDocGenerator)

### SimpleXMlRPCDispatcher如何运行

- register_instance：注册实例self.instance
- register_function：注册函数self.funcs
- register_introspection_function：注册函数self.funcs
- register_multicall_function：注册函数self.funcs
- _marshaled_dispatch：先尝试调用dispatch_method，再尝试调用self._dispatch，最后用xmlrpclib.dumps返回response
- self._dispatch：先尝试使用self.funcs，在尝试使用self.instance

### SimpleXMLRPCRequestHandler如何运行

- 继承BaseHTTPRequestHandler
- do_POST
  - is_rpc_path_valid判断path合法
  - 获取请求数据data
  - server._marshaled_dispath处理data，_dispatch，path，返回response

### SimpleXMLRPCServer如何运行

- 继承SocketServer.TCPServer和SimpleXMLRPCDispatcher
- 调用SimpleXMLRPCRequestHandler.do_POST
- 调用SimpleXMLRPCDispatcher._marshaled_dispatch

### MultiPathXMLRPCServer如何运行

- 继承SimpleXMLRPCServer，但是写了_marshaled_dispatch
- 调用SimpleXMLRPCRequestHandler.do_POST
- 调用MultiPathXMLRPCServer._marshaled_dispatch

### CGIXMLRPCRequestHandler如何运行

- 继承SimpleXMLRPCDispatcher
- handle_request
  - handle_get
  - handle_xmlrpc
- handle_xmlrpc调用SimpleXMLRPCDispatcher_marshal_dispatch

## wsgi

- wsgiref
  - handlers
    - BaseHandler --> SimpleHandler --> BaseCGIHandler --> CGIHandler
  - simple_server
    - SimpleHandler --> ServerHandler
    - HTTPServer --> WSGIServer
	- BaseHTTPRequestHandler --> WSGIRequestHandler
	- demo_app
	- make_server
- WSGIServer通过set_app设置demo_app
- WSGIServer通过WSGIRequestHandler调用ServerHandler
- WSGIServer通过get_app获取demo_app
- ServerHandler通过run运行demo_app