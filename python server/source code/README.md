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

### python3与python2的区别

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

## rpc

## wsgi