from collections import deque

_registry = {}
_msg_queue = deque()

def send(name, msg):
    _msg_queue.append((name, msg))
    
def actor(func):
    def wrapper(*args, **kwargs):
        gen = func(*args, **kwargs)
        next(gen)
        _registry[func.__name__] = gen
    return wrapper
    

@actor
def ping():
    n = yield
    print("ping %d" % n)
    send("pong", 20001)
    
    n = yield
    print("ping %d" % n)
    send("pong", 20002)
    
    
@actor
def pong():
    n = yield
    print("pong %d" % n)
    send("ping", 10002)
    
    n = yield
    print("pong %d" % n)
    send("ping", 10003)
    

def run():
    while _msg_queue:
        try:
            name, msg = _msg_queue.popleft()
            _registry[name].send(msg)
        except StopIteration:
            pass
           
ping()
pong()
send('ping', 10001)
run()