## 教程

- [Spring框架简介](https://www.ibm.com/developerworks/cn/java/wa-spring1/)
- [Spring框架学习](http://blog.csdn.net/lishuangzhe7047/article/details/20740209)
- [Spring教程](http://wiki.jikexueyuan.com/project/spring/)
- [Spring教程|易百教程](http://www.yiibai.com/spring/)

## Spring容器

- @Configuration
- @EnableAutoConfiguration
- @ComponentScan
- @SpringBootApplication = @Configuration + @EnableAutoConfiguration + @ComponentScan

## IOC（控制反转），DI（依赖注入）

### bean factory

- 工厂模式
  - 单例
  - 原型

### 注册

- xml
- 类注解
  - @Component
  - @Controller：Action
  - @Service：Service
  - @Repository：Dao
- 方法注解
  - @Configuration/@Bean

### 使用
  
- @Autowired
- @Resource
- @Injected
  
### 参考

- [Spring IOC有什么好处呢？](https://www.zhihu.com/question/23277575)
- [Spring整理系列(11)——@Configuration注解、@Bean注解以及配置自动扫描、bean作用域](http://blog.csdn.net/javaloveiphone/article/details/52182899)
- [Spring初探之bean工厂（上）](http://blog.csdn.net/windy83/article/details/7405032)
- [Spring初探之bean工厂（下）](http://blog.csdn.net/Windy83/article/details/7407546)
- [通过annotation(注解)实现BeanFactory工厂模式(三)](https://my.oschina.net/u/923324/blog/832269)

## AOP（面向切片编程）

- [什么是面向切面编程AOP？](https://www.zhihu.com/question/24863332)
- [为什么要用spring的IOC和AOP?用了IOC和AOP的优点缺点是什么?](https://www.zhihu.com/question/19993030)
- [SpringAOP基本用法(上)](https://zhuanlan.zhihu.com/p/25892085)
- [SpringAOP基本用法(中)](https://zhuanlan.zhihu.com/p/25892058)
- [SpringAOP基本用法(下)](https://zhuanlan.zhihu.com/p/25891989)
- [spring AOP是什么?你都拿它做什么?](https://zhuanlan.zhihu.com/p/28097563)

## 例子

- [web](https://github.com/gaoxinge/bible/tree/master/java/spring/1)
- [nonweb1](https://github.com/gaoxinge/bible/tree/master/java/spring/2)
- [nonweb2](https://github.com/gaoxinge/bible/tree/master/java/spring/3)