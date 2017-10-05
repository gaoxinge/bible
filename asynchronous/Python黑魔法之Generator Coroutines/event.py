from abc import ABCMeta, abstractmethod
from time import time

events = []

def run(tasks):
    for task in tasks:
        _next(task)
        
    while events:
        for event in events:
            if event.is_ready():
                events.remove(event)
                callback = event.get_callback()
                callback()
                break
                
def _next(task):
    try:
        event = next(task)
        event.set_callback(lambda: _next(task))
        events.append(event)
    except StopIteration:
        pass
        
class Event(object):

    __metaclass__ = ABCMeta
    
    def __init__(self, *args, **kwargs):
        pass
    
    @abstractmethod
    def is_ready(self):
        pass
        
    def set_callback(self, callback):
        self.callback = callback
        
    def get_callback(self):
        return self.callback
        
class sleep(Event):
    
    def __init__(self, timeout):
        self.timeout = timeout
        self.start_time = time()
        
    def is_ready(self):
        return time() - self.start_time >= self.timeout
        
def task(name):
    print(name, 1)
    yield sleep(1)
    print(name, 2)
    yield sleep(2)
    print(name, 3)

tasks = [task('gxg'), task('ryy')]    
run(tasks)