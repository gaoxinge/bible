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
ThreadingMinIn + UnixStreamServer = ThreadingUnixStreamServer
ThreadingMinIn + UnixDatagramServer = ThreadingUnixDatagramServer
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

### select, multiprocess, multithread

### mixin要放在前面

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
- CGIHTTPRequestHandler

## rpc

## wsgi