from selectors import (
    DefaultSelector,
    EVENT_READ,
    EVENT_WRITE,
)
import socket
from types import coroutine


@coroutine
def spawn(task):
    child = yield 'spawn', task
    return child


@coroutine
def accept(sock):
    yield (EVENT_READ, sock)
    connection, address = sock.accept()
    return connection, address


@coroutine
def recv(sock, size):
    yield (EVENT_READ, sock)
    return sock.recv(size)


@coroutine
def send(sock, data):
    yield (EVENT_WRITE, sock)
    sock.send(data)


@coroutine
def tcp_socket(host, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind((host, port))
    sock.listen(5)
    sock.setblocking(False)
    yield
    return sock


async def handle(connection, address):
    print("connection from", address)
    while True:
        data = await recv(connection, 65536)
        if not data:
            break
        await send(connection, data)
    connection.close()
    print("connection close")


async def hello():
    sock = await tcp_socket("127.0.0.1", 8000)
    while True:
        connection, address = await accept(sock)
        await spawn(handle(connection, address))


def run_until_complete(task):
    tasks = [(task, None)]

    selector = DefaultSelector()

    while tasks or selector.get_map():

        timeout = 0 if tasks else None
        if selector.get_map():
            for key, events in selector.select(timeout):
                tasks.append((key.data, None))
                selector.unregister(key.fileobj)

        queue, tasks = tasks, []
        for task, data in queue:
            try:
                data = task.send(data)
            except StopIteration:
                pass
            else:
                if data and data[0] == EVENT_READ:
                    selector.register(data[1], EVENT_READ, task)
                elif data and data[0] == EVENT_WRITE:
                    selector.register(data[1], EVENT_WRITE, task)
                elif data and data[0] == 'spawn':
                    tasks.append((data[1], None))
                    tasks.append((task, data[1]))
                else:
                    tasks.append((task, None))


run_until_complete(hello())
