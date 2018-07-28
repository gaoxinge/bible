import socket
from concurrent.futures import ThreadPoolExecutor


def request():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(("127.0.0.1", 8000))
    sock.send("hello world".encode())
    print(sock.recv(63356).decode())
    sock.close()


with ThreadPoolExecutor(max_workers=4) as pool:
    for _ in range(100):
        future = pool.submit(request)
        future.result()