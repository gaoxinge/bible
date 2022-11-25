## 规范

- [对JAVAEE、规范的一点理解](http://www.iteye.com/topic/1125848)
- [Java EE启示录](https://www.cnblogs.com/hyddd/archive/2010/02/03/1662333.html)
- [javaEE规范和SSH三大框架到底有什么关系](http://blog.csdn.net/bingjing12345/article/details/20641891)

## 实现

- tomcat：servlet，jsp容器
- jetty：servlet容器
- gretty：gradle插件，支持tomcat，jetty
- glassfish：JEE容器
- jboss：JEE容器
- tomee：JEE容器，主要包含tomcat

## 改进

- structs
- spring
  - spring framework
    - spring mvc
  - spring boot
  - spring cloud
  - spring cloud data flow
- hibernate

## 分层

- structs：servlet，contorller
- spring mvc：servlet，contorller

```
structs           -->  spring             --> hibernate
   |                     |                      |
   |                     |                      |
action（表示层）  -->  service（业务层）  -->  dao（持久层）
   |                     |                      |
   |                     |                      |
controller        -->  service            --> model
```