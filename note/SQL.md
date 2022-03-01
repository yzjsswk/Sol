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

case表达式
: `case 列名 when 条件值 then 返回值 else 返回值 end`
`case when 条件表达式 then 返回值 else 返回值 end`

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


