## 0 关于此文

目的是形成一套集 **查询** 与 **八股** 的手册

* [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

* 以 [《C++ Primer Plus》](https://www.kdocs.cn/l/cbUGSlyNNZ5o) 为主线

* 以 [《Effective C++》](https://www.kdocs.cn/l/cjUist8CmOmt) 与 [《More Effecitve C++》](https://www.kdocs.cn/l/clykya3sDwyW) 、[《Effective Modern C++》](https://www.kdocs.cn/l/ckkj7wm8s8lg) 为规范

* 以 [cppreference.com](https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5) 与 [C++ 语言参考](https://learn.microsoft.com/zh-cn/cpp/cpp/cpp-language-reference?view=msvc-170)、[ILE C/C++ 语言参考](https://www.ibm.com/docs/zh/i/7.5?topic=c-ile-cc-language-reference) 为标准

* 其他参考 [cpp 面试指北](https://csguide.cn/cpp/intro.html)、[C++语言面试问题集锦](https://cppguide.cn/pages/cppinterviewmostaskedquestions01/)、[C++ 语言面向对象](https://docs.net9.org/languages/c-oop/)、[C++ 运算符号重载](https://www.runoob.com/cplusplus/cpp-overloading.html)



<br>

---

## 1 预备知识

### 支持的编程范式

* 过程式编程
* 面向对象编程
* 函数式编程
* 泛型编程
* 元编程

<br>

---

### 程序如何运行

> 通俗的，计算机是如何看懂我给它下达的指令？
> 
> 具体的，如何把 `.cpp`（文本文件） -> `.out`（可执行文件）？

文本文件 `.cpp` -> **预处理 -> 编译 -> 汇编 -> 链接** -> 可执行文件 `.out`

**预处理**

* 一个文本替换工具，它会根据源文件中的预处理指令，修改源文件

* 预处理指令以 `#` 开头，如 `#include`、`#define` 等

* `#define` （宏定义）会把指定的内容替换到当前文件中

    ```cpp
    #define MAX 100

    int a[MAX];               // int a[100]; 定义一个大小为 100 的数组
    printf("%d", MAX * MAX);  // printf("%d", 100*100); 输出 10000
    ```

    > 但并不建议使用 `#define` 定义常量，因为它不会进行类型检查，容易出错
    
    C 语言自带一些宏定义：`__TIME__`，`__FILE__` 等等，更多内容可以参考：[C语言预处理器](https://www.runoob.com/cprogramming/c-preprocessors.html)
    
    ```cpp
    printf("%s", __TIME__);  // 输出当前（预处理器替换时候的）时间
    printf("%s", __FILE__);  // 输出当前文件名
    ```

* `#include` 会把指定的文件内容插入到当前文件中

* 预处理后的文件，以 `.i` 为后缀名

    1. 源文件 `main.c`
            
        ```cpp
        #include <stdio.h>
        #define MAX 100

        int main() {
          int a[MAX];
          printf("%d", MAX * MAX);
        }
        ```

    2. 使用 gcc 生成预处理后的文件 `main.i`
        
        ```bash
        gcc -E main.c -o main.i
        ```

**编译**

* 编译器会把预处理后的文件，翻译成汇编语言

    * 汇编语言是一种低级语言，它使用助记符（mnemonic）代替二进制指令
    
    * 汇编语言是与硬件相关的，不同的硬件有不同的汇编语言

* 汇编语言以 `.s` 为后缀名，如 `main.s`

    1. 使用 gcc 生成汇编文件 `main.s`

        ```bash
        gcc -S main.i -o main.s
        ```

**汇编**

* 汇编器会把汇编语言翻译成机器语言

    * 机器语言使用二进制指令

* 机器语言以 `.o` 为后缀名，如 `main.o`
    
    1. 使用 gcc 生成目标文件 `main.o`
        
        ```bash
        gcc -c main.s -o main.o
        ```

**链接**

* 链接器将多个汇编文件链接成一个可执行文件

* 在 linux 中，可执行文件以 `.out` 为后缀名

* 现有 `a.c` 文件和 `b.c` 文件

    * `a.c`
        ```c
        #include <stdio.h>

        int main(){
            printf("%d", ADD(2, 3));
            return 0;
        }
        ```
    * `b.c`
        ```c
        int ADD(int a, int b){
            return a + b;
        }
        ```

    1. 使用 gcc 生成 `.o` 文件
        ```bash
        gcc -c a.c -o a.o
        ```
        
        `a.o` 中的 `main` 函数调用了 `ADD` 函数，但是 `ADD` 函数的定义并没有找到
        
        > **`gcc` 只检查语法，不检查函数的定义**
        > **`g++` 会检查函数的定义，它会在这里弹出错误**
    
        ```bash
        gcc -c b.c -o b.o
        ```



    2. 使用 gcc 生成可执行文件
        ```bash
        gcc a.o b.o -o main.out
        ```
        
        > **链接器会检查函数的定义，如果找不到定义，就会报错**


<br>

---

## 9 内存模型和名称空间

### 存储说明符和类型限定符

**存储说明符**

* `register`

    * 已被弃用

    * 建议将变量存储在寄存器中

    * 不能取地址


* `static`

    * 静态局部变量

        * 只初始化一次，且在程序运行期间一直存在

    * 静态全局变量 / 静态函数

        * 只能在当前文件中使用

    * 静态成员变量

        * 所有对象共享，而不是每个对象有一份
    
    * 静态成员函数

        * 不属于任何对象，而是属于类

        ```cpp
        class Math {
           public:
            static int add(int a, int b) { return a + b; }
        };

        int main() {
            std::cout << Math::add(2, 3);  // 直接调用
            return 0;
        }
        ```

* `extern`

    * 声明一个变量，但不定义它

    * 告诉编译器，这个变量在其他地方定义，但你可以在当前文件中使用它

    * 通常用于在多个文件中共享全局变量

    * 与 `static` 相反

    * 与 `static` 一起使用时，`extern` 会覆盖 `static`

    ```cpp
    extern int x; // 声明一个变量
    ```

* `mutable`

    * 修饰类的成员变量

    * 允许修改（被 `const` 限定的）对象的成员变量

    ```cpp
    class A {
       public:
        mutable int x;
        int y;
        A() {};
    };

    int main() {
        const A a;
        a.x = 666;  // 可以修改
        // a.y = 888; // 不可以修改
        return 0;
    }
    ```

**类型限定符**

* `const`

    * 常量

    * 修饰变量，表示变量的值不能被修改

    * 修饰函数，表示函数不会修改成员变量

    ```cpp
    const int* p = &x; // 指针指向的值不能被修改，等价于 int const* p = &x;
    int* const p = &x; // 指针不能被修改
    const int* const p = &x; // 指针和指针指向的值都不能被修改
    ```

* `const_cast`

    * 用于去除 `const` 限定符

    ```cpp
    const int x = 666;
    int* p = const_cast<int*>(&x);
    *p = 888;
    ```

* `constexpr`

    * 常量表达式

    * 修饰变量，表示变量的值在编译期间就能确定

    * 修饰函数，表示函数的返回值在编译期间就能确定（如果函数的参数也是常量表达式）

    ```cpp
    constexpr int x = 666;
    int constexpr add(int a, int b) { return a + b; }
    ```




* `volatile`

    * 告诉编译器，变量的值可能会在程序的控制之外被修改

    * 通常用于多线程、中断处理等

    ```cpp
    volatile int x;
    ```

<br>

---

### 内存分区

从 **高** 地址到 **低** 地址：

1. 内核空间 `env`

    * 内核处理系统调用、硬件交互、进程调度等

2. 栈区 `stack`

    * 向 **低** 地址方向增长

    ```cpp
    class A{
    public:
      int a;
    };
    ```

    ```cpp
    void func(){
      int a1; // 栈区
      A a2;   // 栈区
      return ;
    }
    ```


3. 动态链接库（文件映射区）


4. 堆区 `heap`

    * 向 **高** 地址方向增长

    ```cpp
    void func(){
      int* a3 = new int;  // 堆区
      A* a4 = new A;      // 堆区
      return ;
    }
    ```

5. 静态区 `static`

    * 有时也称 **全局区** `global`，这俩在内存中同一块区域

    * 向 **高** 地址方向增长

    * 按照初始化方式分为：

        * 静态局部变量

            ```cpp
            void func(){
              static int a7;      // 静态局部变量，在 .bss 段
              static int a8 = 8;  // 静态局部变量，在 .data 段
              return ;
            }
            ```

        * 静态全局变量

            ```cpp
            static int a5;    // 静态全局变量，在 .bss 段
            static int a6 = 6;// 静态全局变量，在 .data 段
            ```

        * 全局变量

            ```cpp
            int a9;       // 全局变量，在 .bss 段
            int a10 = 10; // 全局变量，在 .data 段
            ```

        * 常量区 `.rodata`，read only data

            * 与前三种所在的内存区域不连续

            ```cpp
            const int a11 = 1;  // 常量，在 .rodata 段
            const char* p = "1";// 常量，在 .rodata 段
            ```

6. 代码区 `.text`

    * 存放程序的代码（可执行文件）

    ```cpp
    void func(){  // 函数入口在代码区
      return ;
    }
    ```

<br>

---

### 存储持续性（生命周期）

**自动存储持续性**

* 函数内部的局部变量

* 函数调用时分配内存，函数结束时释放内存

**静态存储持续性**

* 全局变量、静态变量

* 程序运行时分配内存，程序结束时释放内存

**动态存储持续性**

* `new`、`malloc` 分配的内存

* 手动创建，手动释放

**线程存储持续性**

* `thread_local` 修饰的变量

* 每个线程有一份独立的变量

<br>

---

### 作用域

**代码块**

* 由 `{}` 包围的区域

**全局**

* `{}` 外部的区域

<br>

---

### 链接性

**外部链接性**

* 在 `{}` 外部定义，且没有使用 `static` 修饰

**内部链接性**

* 在 `{}` 内部定义，且使用 `static` 修饰


<br>

---

### 命名空间

```cpp
namespace A{
  int a = 1;
  namespace B{  // 允许嵌套
    int a = 2;  // A::B::a
  }
}
```

<br>

---

## 10 对象和类

### 三大特性

**封装**

* 将客观事物抽象为类，隐藏实现细节，只提供接口

* 对内部数据提供了不同级别的访问权限，以保护数据

**继承**

* 子类可以继承（或者扩展）父类的属性和方法

* 通过继承，可以实现代码的复用

* 主要有两种继承的概念：**实现继承** 和 **接口继承**

    * **实现继承** 是指（子类）继承（父类）的实现

        ```cpp
        #include <iostream>

        class A {
           public:
            A() { std::cout << 666 << std::endl; }
        };

        class B : public A {};

        int main() {
            B b;  // 666
            return 0;
        }
        ```

    * **接口继承** 是指（子类）继承（父类）的接口

        > 即，使用 **纯虚函数** 的 **动态多态**

**多态**

* 多种形态：同一个接口，不同的表现

    1. 动态（运行时）多态，通过（继承+虚函数）实现

        ```cpp
        #include <iostream>

        class A {
           public:
            virtual void func1() = 0;                                // 纯虚函数必重写
            virtual void func2() { std::cout << 666 << std::endl; }  // 虚函数可选重写
        };

        class B : public A {
           public:
            void func1() override { std::cout << 888 << std::endl; }
            // void func2() override { std::cout << 555 << std::endl; }
        };

        int main() {
            A *a = new B;
            a->func1();  // 888
            a->func2();  // 666
            return 0;
        }
        ```

    2. 静态（编译时）多态

        * 函数重载

        * 运算符重载

***虚函数***

* 类中有纯虚函数，这个类是抽象类，抽象类不能实例化

* 类中有纯虚函数，子类没有实现这个函数，子类也是抽象类

* 类继承了抽象类，只有实现了抽象类中的纯虚函数，这个类才能实例化

```cpp
class A {
   public:
    virtual ~A() = default;    // 存在虚函数时，析构函数也应该是虚函数
    virtual void func2() = 0;  // 必须重写（纯虚函数）
    virtual void func1() { std::cout << 6 << std::endl; }        // 可选重写
    virtual void func3() final { std::cout << 8 << std::endl; }  // 不可重写
};
```

* 虚函数表 V-Table

    * 当一个类中有虚函数时，编译器会在对象中添加一个指向虚函数表的指钋
    * 当子类重写了父类的虚函数，子类会有自己的虚函数表
    * 存储在静态区中的 `.rodata` 段

* 虚函数表指针 V-Table Pointer

    * 如果一个类中有虚函数，那么这个类的对象中会有一个指向虚函数表的指针
    * 存储在对象的内存中（对象在哪个内存区域，这个指针就在哪个内存区域），通常是对象的第一个成员



<br>

---

### 访问控制

<center>

| 访问控制符 | public | protected | private |
|:----------:|:------:|:---------:|:-------:|
| 内部       | 🟢     | 🟢        | 🟢      |
| 外部       | 🟢     |           |         |


| 继承方式 \ 不同成员在派生类            | public | protected | private |
|:--------------------:|:------------------------:|:----------------------:|:---------------------:|
| **public 继承（内）**     | 🟢 仍为 public            | 🟡 仍为 protected   |                 |
| **public 继承（外）**     | 🟢 仍为 public            |                  |                 |
| **protected 继承（内）**  | 🟡 作为 protected         | 🟡 仍为 protected    |                 |
| **protected 继承（外）**  |                    |                  |                 |
| **private 继承（内）**    | 🔴 作为 private           | 🔴 作为 private         |                 |
| **private 继承（外）**    |                    |                  |                 |



</center>


简单来说：

* 如果是 `public` 继承，那么派生类的访问权限不会改变

* 如果是 `protected` 继承，那么派生类最高的访问权限是 `protected`

* 如果是 `private` 继承，那么派生类最高的访问权限是 `private`

<br>

---


### 构造函数

**默认构造**

```cpp
class A {
public:
  //A() = default;
};
```

* 如果类中没有定义：

    1. 构造函数
    2. 拷贝构造函数
    3. 移动构造函数
  
  那么编译器会自动生成一个默认构造函数

* 也可以显式声明一个默认构造函数

**初始化列表**

```cpp
class A{
public:
  A(int a, int b): _x(a), _y(b){};
  // 在构造函数主体运行之前初始化类成员
private:
  int _x, _y;
};
```

**拷贝构造**

```cpp
#include <iostream>

class A {
public:
  std::string x = "";
  int *y = nullptr;

  // 默认拷贝构造（浅拷贝）
  //A(const A &a) : x(a.x), y(a.y) {}

  // （非默认）拷贝赋值运算符（深拷贝）
  A &operator=(const A &a) {
    // 自我赋值检查
    if (this == &a)
      return *this;

    // 拷贝静态变量
    x = a.x;

    // 拷贝动态变量
    delete y;
    if (a.y == nullptr)
      y = nullptr;
    else
      y = new int(*a.y);

    // 返回当前对象的引用
    return *this;
  }
};

A createA() {
  A a;
  a.x = "xixi";
  a.y = new int(8);
  return a;
}

int main() {
  A a1;
  a1.x = "xixi";
  a1.y = new int(8);
  std::cout << a1.x << " " << &a1.x << " " << a1.y << "\n";

  A a2;
  a2 = a1;          // 赋值初始化，如果没有实现拷贝赋值运算符，则调用拷贝运算函数
  std::cout << a2.x << " " << &a2.x << " " << a2.y << "\n";

  A a3(a1);         // 函数参数传递
  std::cout << a3.x << " " << &a3.x << " " << a3.y << "\n";

  A a4 = createA(); // 返回对象
  std::cout << a4.x << " " << &a4.x << " " << a4.y << "\n";

  return 0;
}

/*
xixi 0x16dc8b388 0x14a704f40
xixi 0x16dc8b358 0x14a704f50
xixi 0x16dc8b338 0x14a704f40
xixi 0x16dc8b318 0x14a704de0
*/
```

* 如果类中没有定义：
    1. 拷贝构造函数
    2. 拷贝赋值运算符
  
  那么编译器会自动生成默认拷贝构造函数和拷贝赋值运算符（浅拷贝）

* 浅拷贝只会拷贝成员变量的值，不会拷贝指针指向的内存

* 深拷贝函数一般自己实现，手动拷贝指针指向的内存

**移动构造**

```cpp
#include <iostream>

class A {
public:
  std::string x = "";
  int *y;

  //A() = default;

  // 默认移动构造
  //A(A &&a) noexcept : x(std::move(a.x)), y(a.y) {}

  // 默认移动赋值运算符
  /*
  A &operator=(A &&a) noexcept {
    // 自我复制检查
    if (this == &a)
      return *this;

    // 移动静态变量
    x = std::move(a.x);

    // 移动动态变量
    delete y;
    y = a.y;

    // 返回当前对象引用
    return *this;
  }
  */
};

int main() {
  A a1;
  a1.x = "xixi";
  a1.y = new int(6);

  std::cout << a1.x << " " << &a1.x << " " << *a1.y << " " << a1.y << "\n\n";

  // 移动构造
  A a2(std::move(a1));
  std::cout << a1.x << " " << &a1.x << " " << *a1.y << " " << a1.y << "\n";
  std::cout << a2.x << " " << &a2.x << " " << *a2.y << " " << a2.y << "\n\n";

  // 移动赋值运算符
  A a3;
  a3 = std::move(a2);
  std::cout << a2.x << " " << &a2.x << " " << *a2.y << " " << a2.y << "\n";
  std::cout << a3.x << " " << &a3.x << " " << *a3.y << " " << a3.y << "\n";

  return 0;
}

/*
xixi 0x16f777388 6 0x12be05f00

 0x16f777388 6 0x12be05f00
xixi 0x16f777358 6 0x12be05f00

 0x16f777358 6 0x12be05f00
xixi 0x16f777338 6 0x12be05f00
*/
```

* 如果类中没有定义：
    1. 移动构造函数
    2. 移动赋值运算符
  
  那么编译器会自动生成默认移动构造函数和移动赋值运算符


有点抽象的是：

|  | 浅拷贝 | 深拷贝 | （默认）移动构造 |
|:-:|:-:|:-:|:-:|
| 值，旧 |  |  | |
| 值，新 | 复制 | 复制 | 复制 |
| 地址，旧 |  |  | |
| 地址，新 | 新的 | 新的 | 新的 |
| *ptr，旧 | | | （不变，不安全） |
| *ptr，新 | 复制 | 复制 | （同旧，不安全） |
| ptr，旧 |  |  | 保持原地址（不变，不安全） |
| ptr，新 | 指向旧地址（共享） | 新地址 | 指向旧地址（共享，不安全） |

> 空的位置意味着不变
>
> 对于支持移动语义的类型，不适用于以上表格
>
> * `std::unique_ptr`，它的移动构造函数会将旧对象的指针置为 `nullptr`
>
> * `std::string`，它的移动构造函数会将旧对象值置为 `""`，但是地址不变


<br>

---


### 析构函数


<br>

---


## 11 使用类


<br>

---

## 1 异常处理

### 1.1 errno

* 一个全局变量，用于存储最后一次调用标准库函数产生的错误代码，需要包含头文件 `errno.h`

* 通常会被 `#define` 为一些别名，如 `EINTR`、`ENOENT` 等

* 使用 `peeror` 输出：

    ```cpp
    perror("打开文件错误"); // 打开文件错误: No such file or directory
    ```

* 使用 `strerror` 输出：

    ```cpp
    std::cout << errno << " " << strerror(errno) << "\n";
    ```

| errno | errno | strerror                                 | note                          |
|-------|-------|------------------------------------------|-------------------------------|
| 1     | EPERM | Operation not permitted                  | 无权操作                      |
| 2     | ENOENT| No such file or directory                | 无此文件或目录                |
| 3     | ESRCH | No such process                          | 无此进程                      |
| 4     | EINTR | Interrupted system call                  | 系统调用中断 <br> `ctrl+c`            |
| 5     | EIO   | I/O error                                | 输入/输出错误                 |
| 6     | ENXIO | No such device or address                | 无此设备或地址                |
| 7     | E2BIG | Argument list too long                   | 参数列表过长                  |
| 8     | ENOEXEC| Exec format error                       | 执行格式错误                  |
| 9     | EBADF | Bad file number                          | 错误文件描述符                 |
| 10    | ECHILD| No child processes                       | 无子进程                      |
| 11    | EAGAIN| Try again                                | 再试 <br> 在 `socket` 中，非阻塞下无数据可读 |
| 12    | ENOMEM| Out of memory                            | 内存不足                      |
| 13    | EACCES| Permission denied                        | 权限被拒绝                    |
| 14    | EFAULT| Bad address                              | 坏地址                        |
| 15    | ENOTBLK| Block device required                   | 需要块设备                    |
| 16    | EBUSY | Device or resource busy                  | 设备或资源忙                  |
| 17    | EEXIST| File exists                              | 文件存在                      |
| 18    | EXDEV | Cross-device link                        | 跨设备链接                    |
| 19    | ENODEV| No such device                           | 无此设备                      |
| 20    | ENOTDIR| Not a directory                         | 非目录                        |
| 21    | EISDIR| Is a directory                           | 是目录                        |
| 22    | EINVAL| Invalid argument                         | 无效参数                      |
| 23    | ENFILE| File table overflow                      | 文件表溢出                    |
| 24    | EMFILE| Too many open files                      | 打开的文件过多                |
| 25    | ENOTTY| Not a typewriter                         | 不是打字机                    |
| 26    | ETXTBSY| Text file busy                          | 文本文件忙                    |
| 27    | EFBIG | File too large                           | 文件太大                      |
| 28    | ENOSPC| No space left on device                  | 设备上无空间                  |
| 29    | ESPIPE| Illegal seek                             | 非法寻道                      |
| 30    | EROFS | Read-only file system                    | 只读文件系统                  |
| 31    | EMLINK| Too many links                           | 链接数过多                    |
| 32    | EPIPE | Broken pipe                              | 管道破裂                      |
| 33    | EDOM  | Math argument out of domain of func      | 数学参数超出函数域            |
| 34    | ERANGE| Math result not representable            | 数学结果不可表示              |
| 35    | EDEADLK| Resource deadlock would occur           | 资源死锁会发生                |
| 36    | ENAMETOOLONG| File name too long                 | 文件名过长                    |
| 37    | ENOLCK| No record locks available                | 无记录锁可用                  |
| 38    | ENOSYS| Invalid system call number               | 无效的系统调用号              |
| 39    | ENOTEMPTY| Directory not empty                   | 目录不空                      |
| 40    | ELOOP | Too many symbolic links encountered      | 符号链接过多                  |
| 42    | ENOMSG| No message of desired type               | 无所需类型的消息              |
| 43    | EIDRM | Identifier removed                       | 标识符已移除                  |
| 44    | ECHRNG| Channel number out of range              | 通道号超出范围                |
| 45    | EL2NSYNC| Level 2 not synchronized               | 2级不同步                     |
| 46    | EL3HLT| Level 3 halted                           | 3级停止                       |
| 47    | EL3RST| Level 3 reset                            | 3级重置                       |
| 48    | ELNRNG| Link number out of range                 | 链接号超出范围                |
| 49    | EUNATCH| Protocol driver not attached            | 协议驱动程序未连接            |
| 50    | ENOCSI| No CSI structure available               | 无CSI结构可用                 |
| 51    | EL2HLT| Level 2 halted                           | 2级停止                       |
| 52    | EBADE | Invalid exchange                         | 无效交换                      |
| 53    | EBADR | Invalid request descriptor               | 无效请求描述符                |
| 54    | EXFULL| Exchange full                            | 交换满                        |
| 55    | ENOANO| No anode                                 | 无阳极                        |
| 56    | EBADRQC| Invalid request code                    | 无效请求代码                  |
| 57    | EBADSLT| Invalid slot                            | 无效插槽                      |
| 59    | EBFONT| Bad font file format                     | 坏字体文件格式                |
| 60    | ENOSTR| Device not a stream                      | 设备不是流                    |
| 61    | ENODATA| No data available                       | 无数据可用                    |
| 62    | ETIME | Timer expired                            | 计时器已到期                  |
| 63    | ENOSR | Out of streams resources                 | 流资源耗尽                    |
| 64    | ENONET| Machine is not on the network            | 机器不在网络上                |
| 65    | ENOPKG| Package not installed                    | 未安装软件包                  |
| 66    | EREMOTE| Object is remote                        | 对象是远程的                  |
| 67    | ENOLINK| Link has been severed                   | 链接已断开                    |
| 68    | EADV  | Advertise error                          | 广告错误                      |
| 69    | ESRMNT| Srmount error                            | Srmount错误                   |
| 70    | ECOMM | Communication error on send              | 发送时通信错误                |
| 71    | EPROTO| Protocol error                           | 协议错误                      |
| 72    | EMULTIHOP| Multihop attempted                    | 尝试多跳                      |
| 73    | EDOTDOT| RFS specific error                      | RFS特定错误                   |
| 74    | EBADMSG| Not a data message                      | 不是数据消息                  |
| 75    | EOVERFLOW| Value too large for defined data type | 值对于定义的数据类型太大      |
| 76    | ENOTUNIQ| Name not unique on network             | 网络上名称不唯一              |
| 77    | EBADFD| File descriptor in bad state             | 文件描述符状态错误            |
| 78    | EREMCHG| Remote address changed                  | 远程地址已更改                |
| 79    | ELIBACC| Can not access a needed shared library  | 无法访问所需的共享库          |
| 80    | ELIBBAD| Accessing a corrupted shared library    | 访问损坏的共享库              |
| 81    | ELIBSCN| .lib section in a.out corrupted         | .lib段在a.out中损坏           |
| 82    | ELIBMAX| Attempting to link in too many shared libraries | 尝试链接太多共享库    |
| 83    | ELIBEXEC| Cannot exec a shared library directly  | 无法直接执行共享库            |
| 84    | EILSEQ| Illegal byte sequence                    | 非法字节序列                  |
| 85    | ERESTART| Interrupted system call should be restarted | 中断的系统调用应重新启动 |
| 86    | ESTRPIPE| Streams pipe error                     | 流管错误                      |
| 87    | EUSERS| Too many users                           | 用户过多                      |
| 88    | ENOTSOCK| Socket operation on non-socket         | 非套接字上的套接字操作        |
| 89    | EDESTADDRREQ| Destination address required       | 需要目的地址                  |
| 90    | EMSGSIZE| Message too long                       | 消息过长                      |
| 91    | EPROTOTYPE| Protocol wrong type for socket       | 协议套接字类型错误            |
| 92    | ENOPROTOOPT| Protocol not available              | 协议不可用                    |
| 93    | EPROTONOSUPPORT| Protocol not supported          | 不支持协议                    |
| 94    | ESOCKTNOSUPPORT| Socket type not supported       | 不支持的套接字类型            |
| 95    | EOPNOTSUPP| Operation not supported on transport endpoint | 传输终点不支持的操作 |
| 96    | EPFNOSUPPORT| Protocol family not supported      | 不支持的协议族                |
| 97    | EAFNOSUPPORT| Address family not supported by protocol | 协议不支持的地址族    |
| 98    | EADDRINUSE| Address already in use               | 地址已在使用                  |
| 99    | EADDRNOTAVAIL| Cannot assign requested address   | 无法分配请求的地址            |
| 100   | ENETDOWN| Network is down                        | 网络不可用                    |
| 101   | ENETUNREACH| Network is unreachable              | 网络无法访问                  |
| 102   | ENETRESET| Network dropped connection because of reset | 网络因重置而断开连接    |
| 103   | ECONNABORTED| Software caused connection abort   | 软件导致的连接中止            |
| 104   | ECONNRESET| Connection reset by peer             | 对等方重置连接                |
| 105   | ENOBUFS| No buffer space available               | 无可用缓冲区                  |
| 106   | EISCONN| Transport endpoint is already connected | 传输终点已连接                |
| 107   | ENOTCONN| Transport endpoint is not connected    | 传输终点未连接                |
| 108   | ESHUTDOWN| Cannot send after transport endpoint shutdown | 终点关闭后无法发送    |
| 109   | ETOOMANYREFS| Too many references: cannot splice | 引用过多：无法拼接            |
| 110   | ETIMEDOUT| Connection timed out                  | 连接超时                      |
| 111   | ECONNREFUSED| Connection refused                 | 连接被拒绝                    |
| 112   | EHOSTDOWN| Host is down                          | 主机不可用                    |
| 113   | EHOSTUNREACH| No route to host                   | 无路由到主机                  |
| 114   | EALREADY| Operation already in progress          | 操作已在进行中                |
| 115   | EINPROGRESS| Operation now in progress           | 操作正在进行中                |
| 116   | ESTALE| Stale file handle                        | 陈旧的文件句柄                |
| 117   | EUCLEAN| Structure needs cleaning                | 结构需要清理                  |
| 118   | ENOTNAM| Not a XENIX named type file             | 不是XENIX命名类型文件         |
| 119   | ENAVAIL| No XENIX semaphores available           | 无XENIX信号量可用             |
| 120   | EISNAM| Is a named type file                     | 是命名类型文件                |
| 121   | EREMOTEIO| Remote I/O error                      | 远程I/O错误                   |
| 122   | EDQUOT| Quota exceeded                           | 超出配额                      |
| 123   | ENOMEDIUM  | No medium found                      | 未找到介质                 |
| 124   | EMEDIUMTYPE| Wrong medium type                    | 错误的介质类型             |
| 125   | ECANCELED  | Operation Canceled                   | 操作被取消                 |
| 126   | ENOKEY     | Required key not available           | 所需密钥不可用             |
| 127   | EKEYEXPIRED| Key has expired                      | 密钥已过期                 |
| 128   | EKEYREVOKED| Key has been revoked                 | 密钥已被撤销               |
| 129   | EKEYREJECTED| Key was rejected by service         | 密钥被服务拒绝             |
| 130   | EOWNERDEAD | Owner died                           | 拥有者已死亡               |
| 131   | ENOTRECOVERABLE| State not recoverable           | 状态不可恢复               |
| 132   | ERFKILL    | Operation not possible due to RF-kill| 由于RF-kill不可能进行操作  |
| 133   | EHWPOISON  | Memory page has hardware error       | 内存页面存在硬件错误       |

### 1.2 异常处理




```cpp
#include <iostream>
#include <fstream>
#include <cstring>

void openfile(std::string filename){
    std::ifstream file(filename);
    if(!file.is_open()) throw std::runtime_error("无法打开文件 " + filename);
    return ;
}

int32_t main(){
    try{
        openfile("txt.txt");
    }
    catch(std::exception& e){
        std::cerr << e.what() << std::endl;
        std::cerr << "errno: " << errno << " " << strerror(errno) << "\n";
    }
    return 0;
}
```

* `try` 尝试

* `throw` 抛出

* `catch` 捕获

<br>

---

## 声明与定义

* **声明** 暂不实现，不分配内存

```cpp
extern int x;
// 声明一个变量
// 告诉编译器，这个变量在其他地方定义，但你可以在当前文件中使用它
void func();
// 声明一个函数
// 确保编译器可以正确地处理函数调用，即使函数的实现可能在其他文件中
class A;
// 前向声明一个类
// 允许在类的实现中使用另一个类而不需要包含其完整定义
```

* **定义** 声明 + 实现，分配内存（类需要具体讨论）

```cpp
int x;          // 定义一个变量
void func(){}   // 定义一个函数
class A{};      // 定义一个类
```


<br>

---

## 智能指针

为了解决内存泄漏、野（wild）指针、悬空（dangling）指针的问题，引入了智能指针

**内存泄漏**

* 含义：申请的内存没有被释放，导致无法再次使用该内存

```cpp
#include <iostream>

int main(){
    while(true)                 // 死循环
        auto* ptr = new int();  // 申请堆空间
    return 0;
}
```

* 原因：忘了 `delete`

* 后果：`Killed`，内存占用过多，程序崩溃


**野指针**

* 含义：指针根本没有正确初始化，指向的是随机内存位置，可能从未被分配过

```cpp
#include <iostream>

int main(){
    int* ptr;
    *ptr = 666;
    return 0;
}
```

* 原因：忘了 `new` 就直接用

* 后果：`Segmentation fault (core dumped)`

**悬空指针**

* 含义：曾经指向有效内存，但由于所指向的内存已被释放或对象生命周期已结束，现在变得无效

* 原因：`delete` 后还在用

```cpp
#include <iostream>

int main(){
    int* ptr1 = new int;
    delete ptr1;
    *ptr1 = 666;        // 此时实际上是越界访问了
    std::cout << "ptr1: " << *ptr1 << "\n";

    int* ptr2 = new int;
    *ptr2 = 888;        // 这个值会覆盖 *ptr1
    std::cout << "ptr1: " << *ptr1 << "\n";
    return 0;
}
```

* 后果：越界访问

<br>

### 创建

```cpp
#include <memory>

std::unique_ptr<int> uniquePtr = std::make_unique<int>();
std::shared_ptr<int> sharedPtr = std::make_shared<int>();
std::weak_ptr<int> weakPtr(sharedPtr);
```

**独占指针 `unique_ptr`**

当 `unique_ptr` 被销毁时，它所指向的对象也被销毁

```cpp
void func(){
    std::unique_ptr<int> ptr = std::make_unique<int>(666);
}   // 当函数结束时, ptr 被销毁, ptr 指向的内存也被销毁
```

**共享指针 `shared_ptr`**

多个 `shared_ptr` 可以指向同一个对象，当最后一个 `shared_ptr` 被销毁时（引用记数为 0 的时候），它所指向的对象也被销毁

```cpp
#include <iostream>
#include <memory>

// 通过引用传递智能指针
// p1 和 p2 指向同一个对象, 引用计数为 2
void f2(std::shared_ptr<int> &p1){
    std::shared_ptr<int> p2 = std::make_shared<int>(666);
    p1 = p2;
    // 此时p2和p1指向同一个对象, 引用计数为 2
    std::cout << p1.use_count() << std::endl;
}

// 创建一个空的智能指针，通过引用传递给f2函数
void f1(){
    std::shared_ptr<int> p1;
    f2(p1);
    // 当 f2 函数执行完毕后, f2 函数内部的 p2 指针被销毁, 引用计数为 1
    std::cout << p1.use_count() << std::endl;
    std::cout << *p1 << std::endl;
}

int main(){
    f1();
    return 0;
}
```



```cpp
ptr.reset();        // 销毁 ptr 指向的内存
ptr.reset(nullptr); // 销毁 ptr 指向的内存（等价）
```

**指针 `weak_ptr`**

为了避免 `shared_ptr` 的循环引用问题，引入了 `weak_ptr`

todo

<br>

---


## 内存管理


<br>

---

## 文件操作

<br>

---

## 面向对象

### 构造：初始化列表



### 构造：拷贝构造

### 构造：移动构造

### 构造：委托构造

### 构造：委派构造

### 重载运算符

```cpp
#include <iostream>

class A{
public:
    A(int x, int y): _x(x), _y(y){};

    // 重载 输出运算符 <<
    friend std::ostream &operator<<(std::ostream& output, A a){
        output << a._x << " " << a._y;
        return output;            
    }
    
    // 重载 输入运算符 >>
    friend std::istream &operator>>(std::istream& input, A a){
        input >> a._x >> a._y;
        return input;            
    }
    
    // 重载 一元运算符 -
    A operator- (){
        return A(-_x, -_y);
    }

    // 重载 二元运算符 +
    A operator+ (A a){
        return A(_x + a._x, _y + a._y);
    }

    // 重载 关系运算符 <
    bool operator< (A a){
        if(_x < a._x) return true;
        if(_x > a._x) return false;
        if(_y < a._y) return true;
        return false;
    }

private:
    int _x, _y;
};

int main(){
    A a(-1, 2);
    std::cout << a << "\n";
    std::cout << -a << "\n";
    std::cout << a+a << "\n";
    std::cout << (a+a<a) << "\n";
    
    return 0;
}
```

<br>

### 继承

**基类**

```cpp
class A{
public:
    void pubShow(){
        std::cout << "A_pub\n";
    }
private:
    void priShow(){
        std::cout << "A_pri\n";
    }
protected:
    void proShow(){
        std::cout << "A_pro\n";
    }
};
```

<br>

**派生**



<br>

### 多态

```cpp
#include <iostream>

class A{
public:
    virtual void pubShow(){
        std::cout << "A_pub\n";
    }
private:
    void priShow(){
        std::cout << "A_pri\n";
    }
protected:
    void proShow(){
        std::cout << "A_pro\n";
    }
};

class B: public A{
public:
    void pubShow(){
        std::cout << "B_pub\n";
    }
};

class C: public A{
public:
    void pubShow(){
        std::cout << "C_pub\n";
    }
};

int main(){
    A* a = new B();
    a->pubShow();

    delete a;
    a = new C();
    a->pubShow();

    return 0;
}
```

<br>

---

## 动态链接

[为什么不能在动态库里静态链接？](https://liam.page/2017/04/03/not-to-link-libstdc-statically-and-why/)







## 异常处理

```c
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// 定义宏 ERRIF，自动计算可变参数的数量
#define ERRIF(flg, ...) do { \
    if (flg == 1){ \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, "\nerrno[%d]: %s\n", errno, strerror(errno)); \
        exit(1); \
    } \
} while (0)

int main(){
    FILE* file = fopen("test.txt", "r");
    ERRIF(file == NULL, "%s 打开错误", "test.txt"); // 使用示例
    return 0;
}
```


**perror**

使用 `perror` 输出错误信息到 `stderr`

```c
perror("Error opening file");
// Error opening file: No such file or directory
```

**stderr**

使用 `fprintf` 和 `strerror` 结合输出到 `stderr`

```c
fprintf(stderr, "Error opening file: %s\n", strerror(errno));
// Error opening file: No such file or directory
```

<br>

---




## 基本数据类型

**整型**

<center>

| type | byte | signed | unsigned |
|:-:|:-:|:-:|:-:|
| `short int`| 2      | \(-2^{15}\) ~ \(2^{15} - 1\) `%hd`  | 0 ~ \(2^{16} - 1\) `%hu` |
| `int`      | 4      | \(-2^{31}\) ~ \(2^{31} - 1\) `%d`  | 0 ~ \(2^{32} - 1\) `%u` |
| `long int` | 8      | \(-2^{63}\) ~ \(2^{63} - 1\) `%ld`  | 0 ~ \(2^{64} - 1\) `%lu`|
| `long long int` | 8      | \(-2^{63}\) ~ \(2^{63} - 1\) `%lld`  | 0 ~ \(2^{64} - 1\) `%llu`|

</center>

历史遗留问题，在不同的平台上，以上类型的长度无法统一

<br>

**精确宽度整数类型**（exact-width integers types）

`#include <stdint.h>`

<center>

| type | byte | signed | unsigned |
|:-:|:-:|:-:|:-:|
|`int8_t` |1| \(-2^{7}\) ~ \(2^{7} - 1\)         | 0 ~ \(2^{8} - 1\) |
|`int16_t`|2| \(-2^{15}\) ~ \(2^{15} - 1\) `%hd` | 0 ~ \(2^{16} - 1\) `%hu`|
|`int32_t`|4| \(-2^{31}\) ~ \(2^{31} - 1\) `%d`  | 0 ~ \(2^{32} - 1\) `%u`|
|`int64_t`|8| \(-2^{63}\) ~ \(2^{63} - 1\) `%ld` | 0 ~ \(2^{64} - 1\) `%lu`|

</center>

值得一提，`int8_t` 是一个 `char` 类型，使用 `cout` 输出需要处理一下

<br>

**最大对象的字节数** `size_t`

`#include <stddef.h>`

<center>

| 平台 | byte | 本质 | range |
|:-:|:-:|:-:|:-:|
| 32 | 4 | `uint32_t size_t` | 0 ~ \(2^{32} - 1\) `%u`|
| 64 | 8 | `uint64_t size_t` | 0 ~ \(2^{64} - 1\) `%lu`|

</center>

<br>

**指针**

指针也是一种数据类型，它用于存储内存地址

<center>

| type | byte | format |
|:-:|:-:|:-:|
| `void*` | 8 | `%p` |

</center>

和其他数据类型一样

* `int` 存储数字

* `char` 存储字符

* `double` 存储浮点数

* **`void*` 存储内存地址**


> **那为何有 `char*`、`int*`、`double*` 等类型呢？**
**指明指针指向的数据类型：**

1. 指针的算术操作

    不同类型的指针运算时，步长不同

    * `char` 占用 1 字节， `char*` 步长为 1。
        ```cpp
        char c = '6';
        char *p = &c;               // p   == 0x0
        printf("%p\n%p", p, p+1);   // p+1 == 0x1
        ```

    * `int32_t` 占用 4 字节， `int32_t*` 步长为 4
        ```cpp
        int32_t i = 6;
        int32_t *p = &i;            // p   == 0x0
        printf("%p\n%p", p, p+1);   // p+1 == 0x4
        ```

2. 类型安全

    编译器会在编译时检查指针的类型，从而避免不同类型的指针直接赋值或比较，确保了在程序中正确使用指针

    ```c
    todo
    ```

<br>

---

## 内存管理

`#include <stdlib.h>`

**申请内存**

`void* malloc(size_t size)`

* 申请 `size` 字节的空间，返回指向这片空间的指针

* 申请失败返回 `NULL`

<br>

**释放内存**

`void free(void *ptr)`

* 释放 `ptr` 指向的内存空间

<br>

---

## 文件操作

此处只整理二进制的方法

**打开文件**

`FILE* fopen(const char* filename, const char* mode)`

* 失败返回 `NULL`

<center>

| type | read | write | add | create | clean | note |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| `rb`  | 🟢 |    |    |
| `wb`  |    | 🟢 |    | 🟢 | 🟢 | 覆盖写入 |
| `ab`  |    |    | 🟢 | 🟢 |    |
| `rb+` | 🟢 | 🟢 |    |    |     | 文首插入 |
| `wb+` | 🟢 | 🟢 |    | 🟢 | 🟢 | 覆盖写入 |
| `ab+` | 🟢 |    | 🟢 | 🟢 |    | 文末追加 |

</center>

**关闭文件**

`int fclose(FILE *fp)`

* 成功返回 `0`

**文件定位**

`int fseek(FILE* fptr, long int offset, int whence)`

* `whence`：偏移起始位

    * `SEEK_SET`：文件开头

    * `SEEK_CUR`：当前位置

    * `SEEK_END`：文件末尾

* `offset`：偏移量

* 成功返回 `0`

**偏移量读取**

`long int ftell(FILE* fptr);`

* 失败返回 `-1`

**读取文件**

`size_t fread(void* ptr, size_t size_of_elements, size_t number_of_elements, FILE* fptr)`

* `ptr`：保存内存位置

* `size_of_elements`：每个元素的大小

* `number_of_elements`：元素的数量

* `fptr`：文件指针

* 成功返回 `number_of_elements`

**写入文件**

``size_t fwrite(void* ptr, size_t size_of_elements, size_t number_of_elements, FILE* fptr)``

* 成功返回 `number_of_elements`


<br>

**分段读取**

```cpp
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MBLOCK 1024 // 1kb

int8_t ERRIF(int8_t flg, const char* msg){
    if(flg == 1){
        perror(msg);
        exit(1);
    }
    return 1;
}

int main(char arg, char* argc[]){
    FILE* fptr_in = fopen(argc[1], "rb");
    ERRIF(fptr_in == NULL, "打开输入文件错误");
    
    FILE* fptr_out = fopen(argc[2], "wb"); 
    ERRIF(fptr_out == NULL, "打开输出文件错误");

    char* ptr = malloc(MBLOCK);
    ERRIF(ptr == NULL, "内存申请失败");

    fseek(fptr_in, 0, SEEK_END);
    size_t flen = ftell(fptr_in);   // 文件大小

    for(size_t i=0; i<flen; i+=MBLOCK){
        fseek(fptr_in, i, SEEK_SET);
        size_t len = i+MBLOCK > flen ? flen-i : MBLOCK;
        printf("%lu\n", len);

        size_t read_len = fread(ptr, 1, len, fptr_in);
        ERRIF(read_len != len, "写入内存错误");
        // deal();

        size_t write_len = fwrite(ptr, 1, len, fptr_out);
        ERRIF(write_len != len, "写入文件错误");
    }

    free(ptr);
    fclose(fptr_out);
    fclose(fptr_in);
    return 0;
}
```

