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

## 3 处理数据

### auto

同 [函数模版](#8-函数探幽) 中的类型推导

* `auto list = {1, 2, 3, 4}`
    
    这里 `list` 的类型是 `std::initializer_list<int>`，元素只读

* `auto x{1]`

    这里 `x` 的类型是 `int`

### decltype


### 类型转换

* `static_cast` 静态类型转换

    ```cpp
    auto x = static_cast<char>(65);
    // 将 int 65 转换为 char 'A'
    ```

* `dynamic_cast` 动态类型转换 

* `reinterpret_cast` 重新解释类型转换

* `const_cast` 去除 `const` 限定符

    ```cpp
    const int x = 666;
    int* p = const_cast<int*>(&x);
    *p = 888;
    ```

<br>

---

## 8 函数探幽

### 引用

```cpp
#include <iostream>

// f1：传值（复制）
// - 参数 res 是值传递，函数接收到的是传入对象的副本
// - 修改 res 不会影响外部原对象
void f1(int res) {
    std::cout << res << std::endl;
}

// f2：左值引用
// - 参数 res 是左值引用，必须传入一个可命名的变量（左值）
// - 修改 res 会影响外部原对象
void f2(int& res) {
    std::cout << res << std::endl;
}

// f3：右值引用
// - 参数 res 是右值引用，只能绑定到右值（临时对象）
// - 虽然是引用，但绑定的是一个临时对象，修改 res 不会影响任何外部变量
void f3(int&& res) {
    std::cout << res << std::endl;
}

int main() {
    int x = 6;
    f1(x);   // 传值，创建副本
    f2(x);   // 左值引用，直接操作 x
    f3(6);   // 右值引用，绑定临时值 6
    return 0;
}
```

### 函数模版

* 模版在编译时被实例化，例如 `mmax(1, 2.0)` 会被实例化为 `double mmax<int, double>(int, double)`

    ```cpp
    template <typename T1, typename T2>
    auto mmax(T1 a, T2 b) {
        return a > b ? a : b;
    }
    ```

* 引用类型推导

    ```cpp
    template <typename T>
    void swap(T &a, T &b) {
        T temp = a;
        a = b;
        b = temp;
    }
    ```

    1. 推导 `T` 的类型时，引用性先被忽略
    
    2. 保留类型限定符
    
    3. 推导出基本类型

    例如 `swap(x,y)`, 且 `x` 和 `y` 都是 `int` 类型，那么
    
    * `T` 为 `int`

    * `a` 和 `b` 的类型为 `int &`

* 指针类型推导

    ```cpp
    template <typename T>
    void swap(T* a, T* b) {
        T c = *a;
        *a = *b;
        *b = c;
    }
    // int a = 5;
    // int b = 10;
    // int* ptr_a = &a;
    // int* ptr_b = &b;
    // swap(ptr_a, ptr_b);
    ```

    同上，如果是 `const int* ptr_a` 则在编译时 `read-only variable is not assignable`

* 按值传递推导

    ```cpp
    template <typename T>
    void f(T x) {
        x = 666;
        std::cout << x << std::endl;
    }
    ```

    例如 `f(x)`，且 `x` 是 `const int&` 类型，那么

    * 忽略引用性，再忽略类型限定符

    * `T` 为 `int`

    * `x` 的类型为 `int`



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

* `mutable`

    * 允许在 `const` 对象中修改成员变量

    * 修改的成员不应该影响对象的逻辑状态，即对象的逻辑状态是 `const`

    ```cpp
    class A {
       public:
        mutable int x;
        A() : x(0) {}
        void setX(int val) const { x = val; }  // 可以修改
    };
    ```

* `constexpr`

    * 常量表达式

    * 修饰变量，表示变量的值在编译期间就能确定

    * 修饰函数，表示函数的返回值在编译期间就能确定（如果函数的参数也是常量表达式）

    ```cpp
    constexpr int x = 666;
    int constexpr add(int a, int b) { return a + b; }
    ```

> 值得一提的是 `enum`，枚举
> ```cpp
> enum nums {
>     ZERO,     // 枚举值从 0 开始
>     ONE = 6,  // 也可以指定枚举值 
>     TWO       // 7, 如果没有指定，枚举值会自动递增
> };
> ```
> 
> 更安全的是强类型枚举 `enum class : int`
> 
> ```cpp
> enum class nums : char {
>     ZERO
>     ONE
>     TWO
> };
> ```

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

<br>

---

### 访问控制

**类内部和外部的访问权限**

| 访问控制符 | 类内部 | 类外部 |
|:----------:|:------:|:------:|
| public     | ✅     | ✅     |
| protected  | ✅     | ❌     |
| private    | ✅     | ❌     |

**继承方式对成员访问权限的影响**

| 继承方式 / 成员类型 | public成员 | protected成员 | private成员 |
|:------------------:|:----------:|:------------:|:-----------:|
| **public继承**      |            |              |             |
| - 派生类内部        | public     | protected    | 无法访问     |
| - 派生类外部        | public     | 无法访问      | 无法访问     |
| **protected继承**   |            |              |             |
| - 派生类内部        | protected  | protected    | 无法访问     |
| - 派生类外部        | 无法访问    | 无法访问      | 无法访问     |
| **private继承**     |            |              |             |
| - 派生类内部        | private    | private      | 无法访问     |
| - 派生类外部        | 无法访问    | 无法访问      | 无法访问     |

**简化规则**

- **public继承**：访问权限保持不变
- **protected继承**：最高访问权限降为 protected
- **private继承**：最高访问权限降为 private

<br>

---

### 虚函数

* 类中有纯虚函数，这个类是抽象类，抽象类不能实例化

* 类中有纯虚函数，子类没有实现这个函数，子类也是抽象类

* 类继承了抽象类，只有实现了抽象类中的纯虚函数，这个类才能实例化

* 不要在构造函数或析构函数中调用虚函数，因为此时虚函数表还没有建立

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


### 构造函数

**默认构造**

```cpp
class A {
   public:
    A() = default;  // 默认构造函数
};
```

* 除了构造/析构函数外，如果不需要其他成员函数，务必使用 `= delete` 删除

    ```cpp
    class A {
       public:
        A() = default;                    // 默认构造函数
        A(const A&) = delete;             // 删除拷贝构造函数
        A& operator=(const A&) = delete;  // 删除拷贝赋值运算符
        A(A&&) = delete;                  // 删除移动构造函数
        A& operator=(A&&) = delete;       // 删除移动赋值运算符
    };
    ```

**初始化列表**

```cpp
class A {
   public:
    A(int a, int b) : _x(a), _y(b) {};  // 在构造函数主体运行之前初始化类成员
   private:
    int _x, _y;
};
```

* 效率更高，没有临时对象的创建和销毁

* `const` 成员必须在初始化列表中初始化

* 明确指定成员的初始化顺序（存在依赖关系）


**拷贝构造** (复制已有对象)

```cpp
class A {
   public:
    // 默认拷贝构造函数(浅拷贝)
    A(const A& a) = default;
    // A(const A& a) : _x(a._x), _y(a._y) {};

    // 默认拷贝赋值运算符(浅拷贝)
    A& operator=(const A& a) = default;
    /*
    A& operator=(const A& a) {
        if (this == &a)
            return *this;  // 自我复制检查
        _x = a._x;         // 拷贝成员变量
        _y = a._y;
        return *this;  // 返回当前对象引用
    }
    */

   private:
    int _x, _y;
};
```

* 浅拷贝只会拷贝成员变量的值，不会拷贝指针指向的内存

* 深拷贝函数一般自己实现，手动拷贝指针指向的内存

**移动构造** (移动已有对象)

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

* 如果基类有虚函数，那么基类的析构函数也应该是虚函数

* 不要在析构函数中抛出异常，析构函数的职责是释放资源，异常处理应当写成一个普通函数


<br>

---

## 11 使用类

### 运算符重载

* 重写 `=` 运算符时，返回值类型应该是 `*this` 的引用，而不是副本

    ```cpp
    class A {
       public:
        int val;
        // 返回类型为自身的引用
        // 参数列表为等号右值
        A& operator=(const A& other) {
            // 检查自赋值
            // 如果当前对象与 other 不是同一个对象
            // 修改当前对象的 val 为 other 的 val
            if (this != &other) {
                val = other.val;
            }
            // 如果是自赋值，返回 *this
            return *this;
        }
    };
    ```

* 当牵扯到动态内存时，重载 `=` 运算符时优先使用 `Copy-and-Swap`

    ```cpp
    class SafeString {
       private:
        char* data;
        size_t length;

       public:
        void swap(SafeString& other) noexcept {
            std::swap(data, other.data);
            std::swap(length, other.length);
        }

        SafeString& operator=(SafeString other) {
            // 按值传递，将 other 的副本传递给当前对象
            // 这样可以确保在发生异常时，原始对象不会被破坏
            // 使用 swap 函数交换数据
            swap(other);
            return *this;
        }
    };
    ```


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

