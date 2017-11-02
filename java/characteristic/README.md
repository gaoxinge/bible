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

## 反射

## 流