try:
    raise OSError
except OSError as e:
    print("get error OSError")
finally:
    print("finally block")