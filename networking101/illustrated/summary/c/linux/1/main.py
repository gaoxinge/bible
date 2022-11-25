import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(("127.0.0.1", 54321))

for data in ["hello", "world", "hello world!"]:
    sock.send(data.encode())
    data = sock.recv(1024).decode()
    print(data)

sock.close()