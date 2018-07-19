from abc import ABCMeta, abstractmethod
from time import time


class Event(object):
    __metaclass__ = ABCMeta

    def __init__(self, *args, **kwargs):
        self.task = None

    def set_task(self, task):
        self.task = task

    def get_task(self):
        return self.task

    @abstractmethod
    def is_ready(self):
        pass


class sleep(Event):
    def __init__(self, timeout):
        self.timeout = timeout
        self.start_time = time()

    def is_ready(self):
        return time() - self.start_time >= self.timeout


def select(event_list):
    ready_event_list = []
    for event in event_list:
        if event.is_ready():
            ready_event_list.append(event)
    return ready_event_list


event_list = []


def run(tasks):
    while any([tasks, event_list]):
        while not tasks:
            ready_event_list = select(event_list)
            for event in ready_event_list:
                event_list.remove(event)
                tasks.append(event.get_task())

        try:
            task = tasks.pop(0)
            _ = next(task)
            if isinstance(_, Event):
                _.set_task(task)
                event_list.append(_)
            else:
                tasks.append(_)
                tasks.append(task)
        except StopIteration:
            pass


def task(name):
    print(name, 1)
    yield sleep(1)
    print(name, 2)
    yield sleep(2)
    print(name, 3)


def task2(name):
    print(name, "task2")
    yield task(name)
    print(name, "task2")

tasks = [task2("a")]
run(tasks)