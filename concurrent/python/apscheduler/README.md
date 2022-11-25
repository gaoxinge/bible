## prepare

### threading.Event

- 标志位：默认为False
- wait：如果timeout不为None，那么阻塞至timeout或者标志位为True；如果timeout为None，那么阻塞至标志位为True
- set：设置标志位为True
- clear：设置标志位为False
- isSet：判断标志位是否为True

### six

## util

## event

## job

- modify
- reschedule
- pause
- resume
- remove
- pending
- _get_run_times
- _modify
- __getstate__
- __setstate__
- __eq__
- __repr__
- __str__
- __unicode__

## triggers

控制调度逻辑。

- date：在指定时间，调度一次
- interval：相隔指定时间，调度一次
- cron：在指定时间，反复调度

## job stores

## executors

### BasePoolExecutor

### pool

- BasePoolExecutor继承BaseExecutor
- ThreadPoolExecutor继承BasePoolExecutor
- ProcessPoolExecutor继承BasePoolExecutor

### gevent

### asyncio

### tornado

### twisted

## schedulers

### BaseScheduler

- configuration
  - \_\_init\_\_：把参数gconfig，options传入configure
  - configure：先判断state是否为STATE_STOPPED；再处理gconfig，放入config；然后把options更新入config；最后调用_configure
  - _configure：依次设置一般options，job defaults，executors，jobstores
  - _create_plugin_instance：通过_trigger_plugins，_trigger_classes，_executor_plugins，_executor_classes，_jobstore_plugins，_jobstore_classes设置
  - Method1
  - Method2
  - Method3
- start
- shutdown
- pause
- resume
- running
- wakeup
- _configure
- _dispatch_event
- _create_plugin_instance
- _create_lock
- _process_jobs
- executors
  - add_executor：添加对应别名的executor
  - remove_executor：移除对应别名的executor
  - _lookup_executor：通过别名查找对应的executor
  - _create_default_executor
- jobstores
  - add_jobstore
  - remove_jobstore
  - _lookup_jobstore
  - create_default_jobstore
- triggers
  - _create_trigger
- listeners
  - add_listener
  - remove_listener
- job
  - add_job
  - scheduled_job
  - modify_job
  - reschedule_job
  - pause_job
  - resume_job
  - get_jobs
  - get_job
  - remove_job
  - remove_all_jobs
  - print_jobs
  - _real_add_job
  - _lookup_job
  
### BlockingScheduler

- 继承BaseScheduler

### BackgroundScheduler

- 继承BlockingScheduler

### GeventScheduler

- 继承BlockingScheduler

### AsyncIOScheduler

- 继承BaseScheduler

### TornadoScheduler

- 继承BaseScheduler

### TwistedScheduler

- 继承BaseScheduler

### QtScheduler

- 继承BaseScheduler

## reference

- [User guide](http://apscheduler.readthedocs.io/en/latest/userguide.html)
- [APScheduler 3.0.1浅析](http://www.cnblogs.com/quijote/p/4385774.html)