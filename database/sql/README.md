## select

```sql
/* 
 * basic select sql
 */
select * from Products; # select all
select prod_name from Products;
select prod_id, prod_name, prod_price form Products;
select distinct vend_id from Products;
select prod_name from Products limit 5;
select prod_name from Products limit 5 offset 5;
```

### order by

```sql
select prod_name from Products order by prod_name;
select prod_id, prod_price, prod_name from Products order by prod_price, prod_name;
select prod_id, prod_price, prod_name from Products order by prod_price desc, prod_name;
```

### where 

```sql
select prod_name, prod_price from Products where prod_price = 3.49;
select vend_id, prod_name from Products where vend_id != 'DLL01';
select cust_name from Customers where cust_email is null;
```

### and, or

```sql
select prod_id, prod_price, prod_name from Products where vend_id = 'DLL01' and prod_price <=4;
select prod_name, prod_price from Products where vend_id = 'DLL01' or vend_id = 'BRS01';
```

### like

```sql
select prod_id, prod_name from Products where prod_name like 'Fish%';
select prod_id, prod_name from Products where prod_name like '__ inch teddy bear';
```

### calculate field

```sql
select vend_name + '(' + vend_country + ')' from Vendors order by vend_name;
select vend_name || '(' || vend_country || ')' from Vendors order by vend_name;
select Concat(vend_name, '(',  vend_country, ')') from Vendors order by vend_name;
select prod_id, quantity, item_price, quantity*item_price as expanded_price from OrderItems where order_num =20008;
```

### function

- text
  - left
  - length
  - lower
  - ltrim
  - right
  - rtrim
  - soundex
  - upper
- date
  - datepart
  - date_part
  - to_char
  - to_number
  - to_date
  - year
  - strftime
- value
  - abs
  - cos
  - exp
  - pi
  - sin
  - sqrt
  - tan
- aggregate
  - avg
  - count
  - sum
  - max
  - min 

```sql
select a.id,a.author,b.count from runoob_tb a inner join tcount_tb b on a.author=b.author;
select a.id,a.author,b.count from runoob_tb a left join tcount_tb b on a.author=b.author;
select b.id,b.author,a.count from tcount_tb a right join runoob_tb b on a.author=b.author;
```

## insert

```sql
insert into runoob_tb (title,author,date) values ("PHP","John Poul",NOW());
insert into runoob_tb (title,author,date) values ("MySQL","Abdul S",NOW());
insert into runoob_tb (title,author,date) values ("JAVA","Sanjay","2007-05-06");
insert into runoob_tb (title,author,date) values ("HTML","gaoxinge","2016-07-24"), ("C++","xinge","2016-07-24"), ("Python","ge","2016-07-23");
insert into runoob_tb2 select title,author from runoob_tb;
```

## update

```sql
update runoob_tb set title="HTML" where id=4;
```

## delete

```sql
delete from runoob_tb where id=4;
```

### 数据类型

MySQL主要有三种数据类型：数值，日期和时间，以及字符串。对于`null`，要用`is null`和`is not null`来判断

### 数据表

```sql
create table runoob_tb(
id int not null auto_increment,
title varchar(100) not null,
author varchar(40) not null,
date date,
primary key (id)
);

create table runoob_tb2(
title varchar(100) not null,
author varchar(40) not null,
);       

drop table runoob_tb;
```

### 字段

```
字段：show columns from runoob_tb2;

添加：alter table runoob_tb2 add id int;

删除：alter table runoob_tb2 drop id;

修改：alter table runoob_tb2 modify id char(10);
      alter table runoob_tb2 change id ide char(10);
      alter table runoob_tb2 modify ide bigint not null default 100;
      alter table runoob_tb2 alter ide set default 1000;
      alter table runoob_tb2 alter ide drop default;

表名：alter table runoob_tb2 rename to tcount_tb;
```

### 索引

索引主要分为一般索引，唯一索引以及主键。他们都可由`create`创建，`alter`修改