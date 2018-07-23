## event3.py

- (sleep(1), future) ---> (task1, future)
- (sleep(2), future) ---> (task1, future)
- (sleep(3), future) ---> (task1, future)

## event4.py

- (sleep(1), future) ---> (task, future) ---> (task2, future)
- (sleep(2), future) ---> (task, future) ---> (task2, future)
