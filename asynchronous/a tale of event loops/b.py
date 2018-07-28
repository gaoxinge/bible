from types import GeneratorType


def hello(name):
    print('hello')
    print('nice')
    yield
    print('nice')
    print('hello')
    print('Hello, %s!' % (name,))


def main():
    print('main')
    print('spawn')
    yield hello('world')
    print('spawn')
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
                if isinstance(data, GeneratorType):
                    tasks.append((data, None))
                tasks.append((task, None))


run_until_complete(main())
