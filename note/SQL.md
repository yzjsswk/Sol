## SQL的四种类型
 |  类型 | 全称 | 说明 |
 | ---- | ---- | ---- | 
 | DDL | Data Definition Language | 数据定义语言, 定义数据库对象(数据库, 表, 字段) |   
 | DML | Data Manipulation Language | 数据操作语言, 对数据进行增删改 |  
 | DQL | Data Query Language | 数据控制语言, 查询表中的记录 | 
 | DCL | Data Control Language | 事物控制语言, 创建数据库用户, 控制数据库访问权限 |

## DDL
#### 创建数据库  
```
    create database [if not exists] 数据库名 [default charset 字符集(utf8mb4)] [collate 排序规则]
``` 
```
    create database 数据库名  
    containment = none
    on primary   
    (name = 'studb', filename = 'G:\study\sjk\studb_data.mdf', size = 3MB , maxsize = 500MB , filegrowth = 10%)  
    log on   
    (name = 'studb_log', filename = 'G:\study\sjk\studb_log.ldf', size = 3MB , filegrowth = 1MB)
```
#### 删除数据库
```
    drop database [if exists] 数据库名
```
#### 切换当前数据库
```
    use database 数据库名
```
#### 查询当前数据库  
```
    select database()
```
#### 查询所有数据库  
```
    show databases
```
#### 在当前数据库创建表
```
    create table 表名 (
        字段名 数据类型 [约束] [comment 注释],
        [constraint 约束名 约束类型(字段名) [references 表名(字段名)],]
    ) [comment 注释]
```
```
    create table C (
        CNO char(2) not null primary key,
        CNAME varchar(24) not null,
        CREDIT smallint null DEFAULT 3, 
        PRE_CNO char(2) null,
        constraint PK_SC primary key(SNO, CNO),
        constraint FK_SNO foreign key(SNO) references S(SNO),
        constraint FK_CNO foreign key(CNO) references C(CNO),
    )
```
#### 修改表名
```
    alter table 表名 rename to 新表名
```
#### 删除表
```
    drop table [if exists] 表名
```
#### 重新创新表(清空数据)
```
    truncate table 表名
```
#### 添加字段
```
    alter table 表名 add 字段名 数据类型 [约束] [comment 注释]
```
#### 修改字段(只修改数据类型)
```
    alter table 表名 modify 字段名 新数据类型
```
#### 修改字段(完全修改)
```
    alter table 表名 change 旧字段名 新字段名 数据类型 [约束] [comment 注释]
```
#### 删除字段
```
    alter table 表名 drop 字段名
```
#### 添加主键约束
```
    alter table 表名 add constraint 约束名 primary key (字段名)
```
#### 添加外键约束
```
    alter table 表名
    add constraint 约束名 foreign key (字段名)
    references 表名 (字段名)
```
#### 删除约束
```
    alter table 表名 drop constraint 约束名
```
#### 查询当前数据库所有表
```
    show tables
```
#### 查询表结构
```
    desc 表名
```
#### 查询表的建表语句(详细信息)
```
    show create table 表名
```
## DML
#### 插入 
```
    insert into 表名[(字段名1, 字段名2, ...)] values 
        (值1, 值2, ...),
        (值1, 值2, ...),
        ... 
```
#### 更新
```
    update 表名 set 字段名1 = 值1, 字段名2 = 值2, ... [where 条件]
```
#### 删除
```
    delete from 表名 [where 条件]
```
## DQL
#### 整体框架
```
    select 字段列表 from 表名列表
    [where 条件列表]
    [group by 分组字段列表]
    [having 分组后条件列表]
    [order by 排序字段列表]
    [limit 分页参数]
```

执行顺序
: from->where->group by->having->select->order by->limit

#### 基本查询
```
    select [distinct] 字段1 [as 别名1], 字段2 [as 别名2], ... from 表名 [as 别名] [where 条件]
```

条件运算符
: `>, >=, <, <=, =, !=/<>, and/&&, or/||, not/!, between and, in(), like, is null`

#### 分组查询
```
    select 字段列表 form 表名 [where 条件] group by 分组字段名 [having] 分组后过滤条件
```

聚合函数
: count, max, min, avg, sum

where和having
: where是分组之前进行过滤, 不满足where执行条件不参与分组;
having是对分组查询的结果进行过滤, 执行顺序: where->group by->having
group by分组之后, 查询一般为聚合函数和分组字段, 查询其他字段无意义
聚合函数只能在having中使用, 而不能在where中使用

#### 排序
```
    select 字段列表 from 表名 order by 字段1 排序方式1, 字段2, 排序方式2, ...
```

排序方式
: asc 升序(默认), desc 降序

#### 分页
```
    select 字段列表 from 表名 limit [起始索引,] 查询记录数
```

索引
: 索引从0开始, 起始索引默认为0。
每页n条记录, 查询第k页(k从1开始): limit (k-1)*n, n 

limit
: 不同数据库实现方式不同, limit是mysql的方式

#### 多表查询
内连接: 笛卡尔积的子集, 两者地位相同
```
    隐式: select 表i.字段... from 表1, 表2, 表3... where 表i的字段...
    显示: select ... from 表1 inner join 表2 on 连接条件(笛卡尔积过滤条件)
```
外连接: 把一个表按某种条件连到另一个表上, 被连的表是主体
```
    select ... from 表1 [left/right] outer join 表2 on 连接条件
```
自连接: 内连接或外连接, 自己连接自己

集合运算(需要字段数量和类型对应相同)
```
    union: 并集
    union all:拼接(可重复) 
    intersect: 交集
    except: 差集

    select...
    union [all]
    select...
```

in和exists
: in: 先处理内表, 然后循环判断in的条件, 适合内表小的情况
exists: 先处理外表, 对外表中的每一条记录判断是否存在于内表中, 适合外表小的情况

#### 子查询



## DCL
用户权限
: select, insert, update, delete, alter, drop, create, all/all privileges

user
: 用户信息存储在mysql数据库中的user表中: use mysql
一个user需要用主机名+用户名确定

#### 查询用户
```
    select * from user
```
#### 创建用户
```
    create user '用户名'@'主机名' identified by '密码'
```
#### 修改用户密码
```
    alter user '用户名'@'主机名' identified with mysql_native_password by '新密码' 
```
#### 删除用户
```
    drop user '用户名'@'主机名'
```
#### 查询权限
```
    show grants for '用户名'@'主机名'
```
#### 授予权限
```
    grant 权限列表 on 数据库名.表名 to '用户名'@'主机名'
```
#### 撤销权限
```
    revoke 权限列表 on 数据库名.表名 to '用户名'@'主机名'
```

## 函数

#### 流程函数

```
    if(条件, 值1, 值2) #如果条件为true返回值1, 否则返回值2
    
    ifnull(值1, 值2) #如果值1为空返回值2, 否则返回值1
    
    case
        when 条件1 then 值1
        when 条件2 then 值2
        ...
        else 值n
    end
    
    case 表达式
        when 值1 then 返回值1
        ...
        else 返回值值n
    end

    # case语句从上往下执行, 自带break
```

#### 数值函数

```
    ceil(x) #上取整
    floor(x) #下取整
    round(x, d) #保留d位小数
    mod(x, y) #x%y
    rand() #返回0-1之间的随机数
```

#### 字符串函数

```
    concat(s1, s2...) #拼接
    substring(s, pos, len) #返回s从pos开始len长度的子串
    substring_index(s, index, pos) #将s按index split, 然后返回前pos个, pos从1开始
    replace(s, s1, s2) #将s中所有s1替换为s2
    trim(s) #去掉头尾空白字符
    trim(s from 字段) #删除字段中所有值的s部分
    lower(s), upper(s) #转小写, 大写
    lpad(s, n, p), rpad(s, n, p) #用p填充s的头/尾, 直到达到n个字符
```

#### 日期函数

```
    curdate() curtime() now() #返回当前日期, 时间, 日期和时间
    year(date), month(date), day(date) #返回日期对应的年月日
    date_add(date, interval number day/month/year) #返回date加上对应时间后的日期
    datediff(date1, date2) #返回date2 - date1的天数
```

#### 窗口函数

```
    窗口函数 over (
        partition by 分组字段
        order by 排序字段
    ) 附加列名
```

窗口函数
: 1. row_number(), rank(), dense_rank() # rank不连续, dense_rank 连续
    2. 聚合函数
