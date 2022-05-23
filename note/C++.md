## 引用, const, 左值, 右值

引用底层是用指针实现的 

    区别: 必须初始化且不可转移, 没有++操作, 比指针更安全, sizeof是被引用的变量大小

const是define的替代

    优点: 比define更安全, 可以指定变量类型, 可以指定作用域

左值

    可以通过地址访问的值, 或者说可以被引用的值
    在C++中定义为可以放在等号左边是不对的, 因为const修饰的变量不能放在等号左边, 但可以使用地址访问

右值
    不能取地址的值, 例如字面量, 表达式, 和临时变量(如函数的常规返回值)

函数参数传递

```
#include<bits/stdc++.h>
using namespace std;

void fun1(int a) {
    cout << a << endl;
}

void fun2(int& a) {
    cout << a << endl;
}

void fun3(const int& a) {
    cout << a << endl;
}

int main() {
    int x = 2; 
    double y = 2.3;
    const int z = 5; 
    fun1(x+1); fun1(y); fun1(z); // all ok
    fun2(x+1); fun2(y); fun2(z); // all error
    fun3(x+1); fun3(y); fun3(z); // all ok
    return 0;
}
```

使用const的三个理由

    避免不小心修改不应该修改的数据
    扩大参数接受范围(上面的fun2(z)和fun3(z))
    使函数调用能正确生成临时变量并使用(fun3(x+1)和fun3(y)会生成const int型的临时变量并引用)