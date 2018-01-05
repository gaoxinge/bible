## structure

使用消息队列和putRequest高度解耦WorkerThread和WorkRequest

```
+-------------+                                 +----------------+
|             |  ------ _requests_queue ------> |                |
| threadpool  |                                 |  workerthread  |
|             | <------ _results_queue  ------  |                |
+-------------+                                 +----------------+
```

## example

## WorkRequest

用于包装任务

- callable_：目标函数
- args：参数
- kwds：参数
- requestID：任务id
- callback：回调函数
- exc_callback：错误处理

## WorkerThread

- run：需要注意
```python
if self._dismissed.isSet():
    self._requests_queue.put(request)
    break
```
- dismiss：设置threading.Event()，使WorkerThread退出

## ThreadPool

- workers
  - createWorkers：创建WorkerThread
  - dismissWorkers：dismiss WorkerThread。若do_join为True，则join dismiss_list；否则把dismiss_list加入dismissedWorkers
  - joinAllDismissedWorkers：join dismissedWorkers
- schedule
  - poll
  - wait
- putRequest：传入WorkRequest

## makeRequest