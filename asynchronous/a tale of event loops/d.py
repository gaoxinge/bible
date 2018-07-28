from types import coroutine

@coroutine
def spawn(task):
    print('spawn')
    child = yield ('spawn', task)
    print('spawn', child)
    return child + 1


async def main():
    print('main')
    child = await spawn('task')
    print('main', child)


m = main()
print(m.send(None))
print(m.send(2))