## 操作系统

#### 操作系统四大基本特征

* 并发：同一段时间内多个程序执行
* 共享：系统中的资源可以被内存中多个并发执行的进线程共同使用
* 虚拟：通过时分复用（如分时系统）以及空分复用（如虚拟内存）技术实现把一个物理实体虚拟为多个
* 异步：系统中的进程是以走走停停的方式执行的，且以一种不可预知的速度推进

#### 操作系统的主要功能

* 进程管理/处理机管理：进程控制, 进程同步, 进程通信, 进程调度
* 内存管理：内存分配, 内存保护, 地址映射, 内存扩充
* 设备管理：完成用户IO请求, 为用户进程分配IO设备, 提高IO设备利用率, 提高IO速度, 方便IO的使用
* 文件管理：磁盘存储空间管理，目录管理，文件读写管理以及文件共享和保护(便利性, 安全性)
* 提供用户接口：程序接口（如API）和用户接口（如GUI）

#### 进程的特征

* 动态性(进程是程序的一次执行, 有创建, 活动, 暂停等过程, 是动态的产生, 变化, 消亡的)
* 并发性(多个进程是并发执行的, 引入进程的目的就是使程序并发执行, 提高资源利用率)
* 独立性(进程实体是能独立运行, 独立获得资源, 独立接受调度的基本单位)
* 异步性(由于进程之间相互制约, 进程的执行以一种不可预知的速度向前推进, 且结果不可再现)
* 结构性(进程实体由程序段, 数据段, 进程控制块三部分组成)

#### 进程的状态与转换

五种状态: 运行, 就绪, 阻塞, 创建, 结束
就绪->运行: 被调度
运行->就绪: 让出处理机资源, 可能是由于时间片到了或者被更高优先级进程抢占等
运行->阻塞: 请求资源或等待某一事件完成, 进程会以系统调用的方式请求操作系统提供服务并进入阻塞(主动)
阻塞->就绪: 得到资源或等待的事件完成, 中断处理程序把相应进程的状态由阻塞态转为就绪态(被动)

#### 进程的创建步骤  

1. 分配一个唯一的进程标识号PID, 申请空白的进程控制块PCB, PCB申请失败则进程创建失败
2. 为进程分配资源, 为程序, 数据, 用户栈分配内存空间, 资源不足则阻塞
3. 初始化PCB, 含标志信息, 处理机状态信息, 处理机控制信息, 进程优先级等
4. 插入就绪队列, 等待被调度执行

#### 进程的终止步骤

1. 根据要终止的PID找到对应的PCB, 读出进程状态
2. 若状态是运行则立即终止, 若该进程有子进程则也递归终止
3. 将进程的所有资源归还父进程或操作系统
4. 把它的PCB从所在链表删除

#### 进程的阻塞步骤(阻塞原语Block)

1. 根据要阻塞的PID找到对应PCB, 读出进程状态
2. 若状态是运行则保护现场, 将状态转为阻塞态, 停止运行
3. 把PCB插入相应事件的等待队列

#### 进程唤醒步骤(唤醒原语Wakeup)

1. 在对应事件的等待队列中找到对应的PCB
2. 移除, 并将状态转为就绪态
3. 插入就绪队列, 等待调度

#### 进程切换步骤

1. 保存处理机上下文, 包括程序计数器和其他寄存器
2. 更新原进程PCB信息并移入对应的队列(就绪或阻塞)
3. 选择另一个进程执行并更新其PCB
4. 切换页表以使用新的地址空间，一旦去切换上下文，处理器中所有已经缓存的内存地址一瞬间都作废了
5. 恢复处理机上下文

#### 进程通信方式

1. 共享存储(使用PV操作进行互斥)
   1. 低级方式: 基于数据结构
   2. 高级方式: 基于存储区
2. 消息传递(使用发送消息和接受消息原语)
   1. 直接方式: 直接把消息挂在接受进程的消息缓冲队列上
   2. 间接方式: 发送到某个中间实体(称为信箱), 接受进程从信箱取得消息
3. 管道: 一个连接读写进程的共享文件, 半双工, 速度慢, 容量有限, 需要保证:
   1. 互斥(读进程和写进程对管道互斥访问)
   2. 同步(读完写, 写完读, 读的时候不写, 写的时候不读)
   3. 确认对方存在
4. 客户机-服务器系统
   1. 套接字Socket
   2. 远程过程调用, 远程方法调用 

#### 进程同步方式

1. 硬件同步方式(关中断, Test-and-Set指令, Swap指令, 不符合让权等待)
2. 信号量
3. 管程(大量PV操作分布在程序中带来麻烦且会死锁)

同步应该遵循的原则
: 空闲让进, 让权等待, 忙则等待, 有限等待

#### 进程调度策略

1. 先来先服务
2. 短进程优先
3. 最短剩余时间优先
4. 时间片轮转
5. 优先级队列

#### 进程与线程

1. 进程是资源管理的基本单位, 线程是程序执行的基本单位  
2. 进程是拥有资源的一个独立单位, 线程不拥有系统资源, 但是可以访问属于进程的资源  
3. 进程创建, 撤销, 切换所需要的系统开销显著大于线程, 因为系统要为进程分配或回收系统资源  
4. 线程上下文切换比进程上下文切换快的多
5. 进程之间通信需要一些同步和互斥手段来辅助从而保证数据一致性, 而线程可以直接读写进程的数据段来通信  
6. 线程之间也可以并发执行, 提高了系统吞吐量  

上/下文
: CPU的寄存器和程序计数器的内容  

上下文切换
: CPU把当前任务的状态保存下来，以便下次切换回这个任务时可以再次加载这个任务的状态，  
然后加载下一任务的状态并执行。任务的状态保存及再加载, 这段过程就叫做上下文切换。  

上下文切换举例
: 线程切换, 进程切换, 用户态和内核态之间的切换, 地址空间切换(虚拟内存切换到物理内存)  

引起上下文切换的因素
: 时间片结束, 中断处理, 用户态切换, 多个任务抢占锁资源  

上下文切换带来的问题
: 产生额外开销, 特别是当高并发时执行速度会变慢  

开销
: 直接开销: 保存和恢复现场带来的开销
间接开销: 影响CPU缓存效果 

#### 线程和协程

线程可分为用户级线程和系统级线程
用户级线程的管理都由应用程序完成, 系统感知不到它的存在
用户级线程会绑定到系统级线程执行(1:1, n:1, n:m), 真正执行的还是系统级线程
而协程就是一种轻量级的用户级线程
协程可以做到在同一个线程内的异步

#### 内存分配

##### 连续分配

* 单一连续分配(单道, 内存中永远只有1道程序,不需要内存保护,可以覆盖,有内部碎片,存储器利用率低)
* 固定分区分配(多道, 把内存划分成大小相等或者不等的分区, 有内部碎片, 利用率低)
* 动态分区分配(程序装入时才根据所需内存进行空间分配, 有内部碎片和外部碎片)

动态分区分配的四种分配策略
: 首次适应: 按地址第一个够用的(性能最好)
最佳适应: 可用的里最小的
最坏适应: 挑最大的
邻近适应: 首次适应的基础上每次从上次结束的位置继续向后找

##### 非连续分配

* 分页(把程序和内存都分为大小相等的块去填, 程序的一块叫一页, 内存的一块叫页框, 需要查页表, 涉及快表, 多级页表, 有很少量的内部碎片)
* 分段(把程序按一定标准划分成几段(如代码段、数据段), 内存不划分, 需要查段表, 段号和段内偏移由用户显示提供, 有外部碎片)
* 段页结合(程序分段, 每段再分页, 内存也分对应大小的页框, 需要段表和页表, 有很少量的内部碎片)

##### 内存置换策略(使用了虚拟内存的基础上, 和外存置换)
* 最佳置换(OPT)(置换未来最远使用的页面, 理想情况, 无法实现)
* 先进先出(FIFO)(置换最早进入内存的页面, belady, 抖动, 不好)
* 最近最久未使用(LRU)(置换内存中最后一次使用时间最早的页面)
* 时钟置换(CLOCK)(循环扫描找使用位为0的页面置换, 使用后置1, 跳过后置0, 全0/1选当前位置的)(改进型CLOCK有1个访问位和1个修改位, 分两种遍历,遍历A只找00, 若 遍历B找01且跳过的将访问位置0, 遍历时ABAB...直到成功)

##### 页面分配(虚拟内存方式给进程分配几个页框)
进程拥有的页框集合称为驻留集
某一时刻前一段时间用到的页面集合称为工作集
* 固定分配局部置换(驻留集大小不变)
* 可变分配全局置换(驻留集大小可变, 盲目分配页框)
* 可变分配局部置换(驻留集大小可变, 根据缺页率灵活调整)                      

#### 分页和分段的区别

1. 分页对程序员是透明的，但是分段需要程序员显式划分每个段。
2. 分页的地址空间是一维地址空间，分段是二维的。
3. 页的大小不可变，段的大小可以动态改变。
4. 分页主要用于实现虚拟内存，从而获得更大的地址空间；分段主要是为了使程序和数据可以被划分为逻辑上独立的地址空间并且有助于共享和保护。

#### 为什么虚拟地址空间切换会比较耗时？
进程都有自己的虚拟地址空间，把虚拟地址转换为物理地址需要查找页表，页表查找是一个很慢的过程，因此通常使用Cache来缓存常用的地址映射，这样可以加速页表查找，这个Cache就是TLB（translation Lookaside Buffer，TLB本质上就是一个Cache，是用来加速页表查找的）。

由于每个进程都有自己的虚拟地址空间，那么显然每个进程都有自己的页表，那么当进程切换后页表也要进行切换，页表切换后TLB就失效了，Cache失效导致命中率降低，那么虚拟地址转换为物理地址就会变慢，表现出来的就是程序运行会变慢，而线程切换则不会导致TLB失效，因为线程无需切换地址空间，因此我们通常说线程切换要比较进程切换块，原因就在这里。

#### 死锁产生的四个必要条件

1. 互斥(资源只能被一个进程使用)
2. 请求与保持(进程请求资源, 保持请求不放)
3. 不剥夺(不能停止进程对资源的请求)
4. 循环等待(若干进程之间对进程的请求形成一种循环等待关系)

#### 如何处理死锁

1. 忽略死锁(鸵鸟算法, 用于死锁出现概率比较低的情形)
2. 检测死锁并恢复(资源分配图)
3. 仔细的分配资源来避免死锁产生(银行家算法)
4. 破坏死锁的4个必要条件 
