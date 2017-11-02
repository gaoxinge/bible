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

## 时间日期

## 反射

## 流