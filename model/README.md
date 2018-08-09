## CSP: communicating sequential processes

- go: goroutine and channel
- python: thread and message queue

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

- same language/different language: process and pipe, message queue

## reactor pattern

- reactor pattern: select
- proactor pattern