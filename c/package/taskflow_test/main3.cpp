#include <taskflow/taskflow.hpp>  // Taskflow is header-only

int main(){
  
  tf::Executor executor;
  tf::Taskflow taskflow;
  
  int i = 10;

  tf::Task init = taskflow.emplace([](){ std::cout << "init" << std::endl; }).name("init");
  tf::Task stop = taskflow.emplace([](){ std::cout << "stop" << std::endl; }).name("stop");

  tf::Task cond = taskflow.emplace(
    [&i](){ return i == 0; }
  ).name("cond");
  tf::Task body = taskflow.emplace(
    [&i](){ std::cout << "Hello world! " << i << std::endl; i--; }
  ).name("body");

  init.precede(cond);
  body.precede(cond);
  cond.precede(body, stop);

  executor.run(taskflow).wait(); 

  taskflow.dump(std::cout);

  return 0;
}
