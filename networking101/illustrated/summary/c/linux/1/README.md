- [socket 编程基础知识](https://cizixs.com/2015/03/29/basic-socket-programming/)

```
> docker build -t qwer .
> docker run -it -p 54321:54321 qwer bash
root@d728bf7fa096:/# /main
start server...
listening on 0.0.0.0 54321...
client ip: 172.17.0.1, port: 49552
received: hello
received: world
received: hello world!
received 0 bytes, close. 
```

```
> python main.py
Wed Nov 28 10:10:57 2018: hello
Wed Nov 28 10:10:57 2018: world
Wed Nov 28 10:10:57 2018: hello world!
```