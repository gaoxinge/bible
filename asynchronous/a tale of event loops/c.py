from inspect import iscoroutine
from types import coroutine


@coroutine
def nice():
    print('nice')
    yield
    print('nice')


async def hello(name):
    print('hello')
    await nice()
    print('hello')
    print('Hello, %s!' % (name,))


async def main():
    print('main')
    await hello('world')
    print('main')


def run_until_complete(task):
    tasks = [(task, None)]
    while tasks:
        queue, tasks = tasks, []
        for task, data in queue:
            try:
                data = task.send(data)
            except StopIteration:
                pass
            except Exception as error:
                print(error)
            else:
                if iscoroutine(data):
                    tasks.append((data, None))
                tasks.append((task, None))


run_until_complete(main())
