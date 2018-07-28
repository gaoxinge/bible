def main():
    print('main')
    print('spawn')
    child = yield ('spawn', 'task')
    print('spawn', child)
    child = child + 1
    print ('main', child)


m = main()
m.send(None)
m.send(2)
