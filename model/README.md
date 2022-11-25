## summary

- [Such blocking very concurrency, wow](http://shairosenfeld.com/such_blocking_very_concurrency/#1)
- message pass
  - go: goroutine and channel
  - python: thread and message queue
  - same language/different language: process and pipe, message queue
- worker consumer
  - worker consumer
  - publisher subscriber

## Actor Model (mailbox)

- [Actor Model](https://en.wikipedia.org/wiki/Actor_model)
- [漫谈并发编程：Actor模型](https://www.jianshu.com/p/db04cab86ab9)
- gevent-actor-sample
  - [github](https://github.com/ianjuma/gevent-actor-sample)
  - [blog](https://medium.com/@ianjuma/the-actor-model-in-python-with-gevent-b8375d0986fa)
- Thespian
  - [github](https://github.com/godaddy/Thespian)
  - [doc](https://godaddy.github.io/Thespian/doc/#outline-container-h:e8dd9cdc-1a23-4f11-9d4b-017a12b07593)
  - [pdf](https://godaddy.github.io/Thespian/doc/in_depth.pdf)
- pykka
  - [github](https://github.com/jodal/pykka/tree/master)
- xudd
  - [github](https://github.com/xudd/xudd)
- python-actors
  - [github](https://github.com/tamland/python-actors/)

## CSP: communicating sequential processes (channel)

```python
# -*- coding: utf-8 -*-
import Queue
import threading


def naturaler(out_queue):
    i = 0
    while True:
        if i >= 100:
            out_queue.put(None)
            break
        else:
            out_queue.put(i)
            i += 1


def squarer(out_queue, in_queue):
    while True:
        x = in_queue.get()
        if x is None:
            out_queue.put(None)
            break
        else:
            out_queue.put(x * x)


def printer(in_queue):
    while True:
        x = in_queue.get()
        if x is None:
            break
        else:
            print(x)


def main():
    naturals = Queue.Queue()
    squares = Queue.Queue()

    naturaler_thread = threading.Thread(target=naturaler, args=(naturals,))
    naturaler_thread.start()

    squarer_thread = threading.Thread(target=squarer, args=(squares, naturals))
    squarer_thread.start()

    printer(squares)


if __name__ == "__main__":
    main()
```

## reactor pattern

- reactor pattern: select
  - [Reactor](https://www.cse.wustl.edu/~schmidt/PDF/reactor-siemens.pdf)
  - [Scalable IO in Java](http://gee.cs.oswego.edu/dl/cpjslides/nio.pdf)
- proactor pattern