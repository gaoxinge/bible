## 数字类型和String互相转化

- [java中string和int互相转化](http://blog.csdn.net/memray/article/details/7312817/)

```java
Integer a = Integer.valueOf("123");
String b = a.toString();
```

## 循环

### 数组

```java
public class Test {
    public static void main(String[] args) {
        // java5
        int[] a = {1, 2, 3};
        for (int x: a) {
            System.out.println(x);
        }
    }
}
```

### 可迭代对象

```java
import java.util.*;

public class Test {
    public static void main(String[] args) {
        List<String> a = new ArrayList<>();
        a.add("123");
        a.add("234");
        for (String x: a) {
            System.out.println(x);
        }
    }
}
```

### 流

```java
import java.util.*;

public class Test {
    public static void main(String[] args) {
        // java8
        List<String> a = new ArrayList<>();
        a.add("123");
        a.add("234");
        a.forEach((x) -> {
           System.out.println(x); 
        });
        a.stream().forEach((x) -> {
            System.out.println(x);
        });
    }
}
```

## 正则表达式

```java
import java.util.regex.*;

public class Test {
    public static void main(String[] args) {
        Pattern pattern=Pattern.compile("\\S+?@\\S+?.com");
        Matcher matcher=pattern.matcher("XXX@qq.com");
        System.out.println(matcher.find());
    }
}
```

## 时间日期

```java
import java.util.Date;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.sql.Timestamp;

public class Test {
    public static void main(String[] args) {
        /* Date
         * use SimpleDateFormat to parse
         */
        Date da = new Date();
        SimpleDateFormat ft = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        String s = ft.format(da);
        System.out.println(s);
        
        /* LocalDate
         * LocalDate.now or LocalDate.parse
         */
        LocalDate d = LocalDate.parse("2017-11-02");
        LocalDate c = LocalDate.parse("2017-11-03");
        System.out.println(d.plusDays(1));
        System.out.println(d.isAfter(c));
        
        /* LocalDateTime
         * LocalDateTime.now or LocalDateTime.parse
         * use DateTimeFormat to parse
         */
        LocalDateTime dt = LocalDateTime.parse("2017-11-02T00:00:00.000");
        s = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss").format(dt);
        System.out.println(s);
        
        // Timestamp or System.currentTimeMillis
        long ts = Timestamp.valueOf("2017-11-02 00:00:00").getTime();
        System.out.println(ts);
        ts = System.currentTimeMillis();
        System.out.println(ts);
    }
}
```

## 传递

- [Java到底是值传递还是引用传递？](https://www.zhihu.com/question/31203609)

java的数据类型分为：

- 内置类型
- 引用类型
  - 数组
  - 类

其中引用类型分为：
- 提供改变接口的（相当于python的可变对象）
- 不提供改变接口的（相当于python的不可变对象）

```java
public class Test {
    
    public static void f(int a) {
        a = 2;
    }
    
    public static void g(X b) {
        b = new X(2);
    }
    
    public static void h(X b) {
        b.setX(2);
    }
    
    public static void main(String[] args) {
        int a = 1;
        X b = new X(1);
        
        f(a);
        System.out.println(a);
        
        g(b);
        System.out.println(b.getX());
        
        h(b);
        System.out.println(b.getX());
    }
}

class X {
    
    Integer x;
    
    X(Integer x) {
        this.x = x;
    }
    
    Integer getX() {
        return this.x;
    }
    
    void setX(Integer x) {
        this.x = x;
    }
}
```

## 可变参数

```java
public class Test {
    
    public static double max(double... numbers) {
        double a = 0.0;
        for (int i = 0; i < numbers.length; ++i)
            if (a < numbers[i]) a = numbers[i];
        return a;
    }
    
    public static double min(double... numbers) {
        double a = 0.0;
        for (double number: numbers)
            if (a > number) a = number;
        return a;
    }
    
    public static void main(String[] args) {
        // java5
        System.out.println(max(1.0, 2.0, 3.0));
        System.out.println(max(new double[]{1.0, 2.0, 3.0}));
        System.out.println(min(1.0, 2.0, 3.0));
        System.out.println(min(new double[]{1.0, 2.0, 3.0}));
    }
}
```

## finalize方法

- [java的finalize()函数](http://www.cnblogs.com/iamzhoug37/p/4279151.html)

```java
public class FinalizationDemo {
    public static void main(String[] args) {  
        Cake c1 = new Cake(1);  
        Cake c2 = new Cake(2);  
        Cake c3 = new Cake(3);  
        c2 = null;
        c3 = new Cake(4);
        System.gc();
    }
}  
 
class Cake {
    
    private int id;  
    
    public Cake(int id) {  
        this.id = id;  
        System.out.println("Cake object " + id + " is created.");  
    }  
    
    @Override
    public void finalize() {   
        System.out.println("Cake object " + id + " is disposed.");  
    }  
}
```

## IO流，File类，Scanner类

java的IO流如下：

![IO流](http://www.runoob.com/wp-content/uploads/2013/12/iostream2.png)

java的File类可以操作文件和目录，Scanner类可以从控制台输入：

```java
import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        // java5
        Scanner scan = new Scanner(System.in);
    }
}
```

## 继承

- 子类不能继承父类的构造器
- 如果子类的构造器中没有super关键词，系统会自动调用父类的无参构造器

```java
public class Test {
    public static void main(String[] args) {
        SubClass a = new SubClass(2); // error
    }
}

class SuperClass {
    
    private int n;
    
    // SuperClass() {}
    
    SuperClass(int n) {
        this.n = n;
    }
}

class SubClass extends SuperClass {

   private int n;
   
   SubClass(int n) {
       this.n = n;
   }
}
```

## 多态

- 对象向上转型以后
  - 使用方法，任然使用子类重载的方法
  - 可以使用instanceof判断是不是子类的实例
  - 可以向下转型，保持原信息不变
  
```java
public class Test {
    public static void main(String[] args) {
        Animal a = new Cat(); 
        a.eat();
        Cat c = (Cat) a;
        c.eat();
        
        show(new Cat());
        show(new Dog());
        show(new Animal());
  }
            
    public static void show(Animal a) {
        a.eat();
        if (a instanceof Cat) {
            Cat c = (Cat) a;  
            c.work();
        } else if (a instanceof Dog) {
            Dog c = (Dog) a;  
            c.work();
        }
    }
}
 
class Animal {  
    public void eat() {
        System.out.println("eat something");
    }
    public void work() {
        System.out.println("get something");
    }
}  
  
class Cat extends Animal {    
    public void eat() { 
        System.out.println("eat fish");  
    }  
    public void work() {
        System.out.println("get fish");  
    }  
}  
  
class Dog extends Animal {  
    public void eat() {  
        System.out.println("eat meat");  
    }  
    public void work() {  
        System.out.println("get meat");  
    }  
}
```

## 集合框架

```java
import java.util.*;

public class Test {
    public static void main(String[] args) {
        List<String> list = new ArrayList<>();
        list.add("1");
        list.add("2");
        list.add("3");
        list.addAll(list);
        System.out.println(list);
        System.out.println(list.size());
        
        Object[] array_ = list.toArray();
        for (Object s: array_)
            System.out.print(s + " ");
        System.out.println();
        
        String[] array = new String[list.size()];
        list.toArray(array);
        for (String s: array)
            System.out.print(s + " ");
        System.out.println();
		
        String[] array = new String[]{"1", "2"};
        List<String> list = Arrays.asList(array);
        
        for (String s: list)
            System.out.print(s + " ");
        System.out.println();
        
        for (int i = 0; i < list.size(); ++i)
            System.out.print(list.get(i) + " ");
        System.out.println();
        
        Iterator<String> iter = list.iterator();
        while (iter.hasNext())
            System.out.print(iter.next() + " ");
        System.out.println();
    }
}
```

```java
import java.util.*;

public class Test {
    public static void main(String[] args) {
        Map<String, String> map = new HashMap<>();
        map.put("1", "value1");
        map.put("2", "value2");
        map.put("3", "value3");
        map.putAll(map);
        System.out.println(map);
        System.out.println(map.size());
        
        for (String key: map.keySet())
            System.out.println(key);
        
        for (String value: map.values())
            System.out.println(value);
        
        for (Map.Entry<String, String> entry: map.entrySet())
            System.out.println(entry.getKey() + " " + entry.getValue());
    }
}
```

## 泛型

```java
class A1<T> {}
class A2<T extends Number> {}
```

## 类型通配符

```java
public static void getData1(List<?> data) {}
public static void getData2(List<? extends Number> data) {}
public static void getData3(List<? super Integer> data) {}
```

```java
import java.util.*;

public class Test {
    
    public static List<? extends B> f(int a) {
        List<B> l1 = new ArrayList<>();
        List<C> l2 = new ArrayList<>();
        l1.add(new B(1));
        l2.add(new C(1, 2));
        if (a > 0) return l1;
        else       return l2;
    }
    
    public static void g(List<? extends B> a) {
        System.out.println(a.size());
    }
    
    public static<T> void h(List<T> a) {
        System.out.println(a.size());
    }
    
    public static void main(String[] args) {
        List<? extends B> t1 = f(1);
        List<? extends B> t2 = f(-1);
        
        g(t1);
        g(t2);
        h(t1);
        h(t2);
        System.out.println(t1.get(0).getX());
        System.out.println(t2.get(0).getX());
        
        List<C> t3 = (List<C>) f(-1); 
        System.out.println(t3.get(0).getY());
    }
}

class B {
    private Integer x;
    public B(Integer x) {this.x = x;}
    public Integer getX() {return this.x;}
    public void setX(Integer x) {this.x = x;}
}

class C extends B {
    private Integer y;
    public C(Integer x, Integer y) {
        super(x);
        this.y = y;
    }
    public Integer getY() {return this.y;}
    public void setY(Integer y) {this.y = y;}
}

```

## 反射

## 流