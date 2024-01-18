---
toc:
    depth_to: 3
html:
    toc: true   # 打开侧边目录
export_on_save:
    html: true  # 自动保存
---

# 参考

关于 C++ 的学习参考：

* [cppreference](https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5)：C++ 参考手册

* [Microsoft Visual C++](https://learn.microsoft.com/zh-cn/cpp/cpp/cpp-language-reference?view=msvc-170)：微软官方 C++ 参考手册


<br>

---

# class

> 假设，我们需要接受一个不确定的输入，
> 如果这个输入是一个整数，那么我们就输出这个整数的平方，
> 否则，不输出。

以，**面向过程** 的思想，我们可以这样写：

```cpp
// 定义一个字符串，接受输入
std::string s;
cin>>s;
// 判断输入是否为整数
bool isInt = true;
for(int i = 0; i < s.size(); i++)
    if(s[i] < '0' || s[i] > '9'){
        isInt = false;
        break;
    }
// 判断输入是否超过 int 的范围
if(isInt)
    if(s.size() > 10 || (s.size() == 10 && s > "2147483647"))
        isInt = false;
// 输出
if(isInt)
    cout<<s;
else
    cout<<"不是整数";
```

以，**面向对象** 的思想，我们可以这样写：

```cpp
Input *userInput = new Input(); // 定义一个输入类
userInput->getNum();            // 接受输入
userInput->printNum();          // 输出
delete input;                   // 释放内存
```

可以发现，**面向对象** 的思想，使得代码更加简洁、易读、易维护。

但这并不意味着，**面向对象** 思想就是最好的，只是在某些场景下，**面向对象** 思想更加适用。

于是 C++ 引入了 **类** 的概念，使得我们可以更加方便地使用 **面向对象** 思想。

<br>

类的基本思想是 **数据抽象** 和 **封装**。
**数据抽象** 是一种依赖于 **接口** 和 **实现** 分离的编程（设计）技术。

> 例如，我们需要实现一个功能，此功能需要
> * 若干个变量
> * 若干个变量需要进行若干个操作（函数）
> 
> 于是，我们可以将这些变量和函数封装在一个类中，这样就实现了 **数据抽象** 和 **封装**。

> 更加具体的，我们要设计一个水杯类
> * 水杯有水量
> * 水杯可以加水
> * 水杯可以倒水
> 
> 于是，我们可以将 **水量** 和 **加水倒水** 封装在一个类中，这样就是可以非常方便的使用这个水杯了。
> 
> 对于使用类的我们而言，只需要知道水杯有水量，可以加水倒水即可，加水倒水就是 **接口**。
>
> 至于，这个水能不能加，能加多少，能倒多少，这些都是 **实现**，我们不需要知道。

<br>

---

## 封装：定义一个抽象数据类型

>封装是指将 **数据** 和 **操作数据的函数** 绑定在一起，数据被保护在内部，外部程序只能通过已定义的接口访问数据，这样就确保了数据的完整性、安全性。

在这里，抽象数据类型，就是 **类**。



```cpp
// Cup.h
#pragma once

class Cup
{
public:
	Cup(const int w=99);// 构造函数
	~Cup();				// 析构函数

	int getWater() const;		// 取得水量
	void addWater(const int w);	// 加水
	void pourWater(const int w);// 倒水
private:
	int* _water;	// 水量
	int* _volume;	// 容量
};
```

* `Cup(const int w=99);`
    * `int w`，此函数需要传入一个 `int` 类型的参数。
    * `const`，此函数不会修改传入的参数。
    * `=99`，此函数的默认参数为 `99`，如果不传入参数，那么就会使用默认参数。

* `int getWater() const;`
    * `int`，此函数返回一个 `int` 类型的值。
    * `const`，此函数不会修改类的成员变量。

```cpp
// Cup.cpp
#include "Cup.h"

Cup::Cup(const int w) {
	this -> _water = new int;	
	_volume = new int;

	*_water = 0;		// 初始水量为0
	*_volume = w;		// 容量为w
}

Cup::~Cup() {
	delete _water;		// 释放水量
	delete _volume;		// 释放容量
}

int Cup::getWater() const {
	return *_water;
}

void Cup::addWater(const int w) {
	// 加水加到最大容量
	if (*_water + w > *_volume) {
		*_water = *_volume;
		return;
	}
	*_water += w;
}

void Cup::pourWater(const int w) {
	// 倒水倒到最少容量
	if (*_water - w < 0) {
		*_water = 0;
		return;
	}
	*_water -= w;
}
```

* `this -> _water = new int;`
    * `this` 指向当前对象，`this -> _water` 指向当前对象的 `_water` 成员变量。
    * 当我们调用 `_water` 时，实际上是调用 `this -> _water`。
    * 任何一个成员都有一个隐含的 `this` 指针，指向调用它的对象。

```cpp
// main.cpp
#include "Cup.h"
#include <iostream>

int main() {
	Cup* cup = new Cup(100);
	std::cout<<cup->getWater()<<std::endl;
	// 输出 0
	cup->addWater(150);
	std::cout<<cup->getWater()<<std::endl;
	// 输出 100
	cup->pourWater(50);
	std::cout<<cup->getWater()<<std::endl;
    // 输出 50
	delete cup;
	return 0;
}
```

## 继承：定义一个基类的派生类

我们更想，来一杯 **蜜雪冰冰**🥤！

我们简单考虑一下：
| 水杯 | 蜜雪冰冰 |
|:-:|:-:|
| 水量 | 水量 |
| 加水 | 加水 |
| 倒水 | 倒水 |
| - | 加波波脆 |
| - | 加芋圆 |
| - | 小料表 | 

可以发现，蜜雪冰冰是水杯的一种，蜜雪冰冰继承了水杯的所有东西，同时，蜜雪冰冰还有自己的东西。

因此，我们就没有必要重新定义一个蜜雪冰冰类，只需要创建一个水杯类的派生类，即可。

```cpp
// mxbb.h
#pragma once
#include "Cup.h"
#include <iostream>

class Mxbb : public Cup {

public:
	Mxbb(const int s = 0);
	~Mxbb();
	void addX();		// 加啵啵脆
	void addY();		// 加芋圆
	void query() const;	// 查询小料添加情况

private:
	bool* _x;	// 啵啵脆
	bool* _y;	// 芋圆

	int calc(const int s);	// 根据中大超杯计算容量
};
```

`class Mxbb : public Cup`
* `Mxbb` 类继承了 `Cup` 类。
* `public`，继承方式为公有继承。此话题暂不讨论。

```cpp
#include "Mxbb.h"

int Mxbb::calc(const int s) {
    int res = 500;              // 中杯容量为500
    if (s == 2) res = 700;      // 大杯容量为700
    else if (s == 3) res = 1000;// 超大杯容量为1000
    return res;
}

Mxbb::Mxbb(const int s) : Cup(calc(s)), _x(nullptr), _y(nullptr){
	// 子类 构造函数 的初始化工作
    // 需要显式调用基类的构造函数

    _x = new bool;
    _y = new bool;
    *_x = false;    // 初始无啵啵脆
    *_y = false;    // 初始无芋圆
}

Mxbb::~Mxbb() {
    // 子类 析构函数 的清理工作
    // 不需要显式调用基类的析构函数，它会自动被调用

    delete _x;
    delete _y;
}

void Mxbb::addX() {
	*_x = true;
}

void Mxbb::addY() {
	*_y = true;
}

void Mxbb::query() const{
	std::cout << "芋圆奶茶的小料有";
	if (*_x) std::cout << " 啵啵脆";
	if (*_y) std::cout << " 芋圆";
	std::cout << std::endl;
}
```

## 公有、私有、保护


## 多态：定义一个基类的虚函数
 




---

# namespace

**namespace：命名空间**

有了命名空间，我们就可以将不同的函数、类、变量等放在不同的命名空间中，从而避免命名冲突。

## 命名空间的使用

**在函数中使用**

`jiao` 命名空间中有一个 `print` 函数，`JIAO` 命名空间中也有一个 `print` 函数。
前者输出 666，后者输出 777。

```cpp
#include <iostream>

namespace jiao {
void print(){
    std::cout<<"666";
}
}

namespace JIAO {
void print(){
    std::cout<<"777";
}
}

int main(){
    jiao::print();  // 输出 666
    JIAO::print();  // 输出 777
    return 0;
}
```

<br>

**在类中使用**

`jiao` 命名空间中有一个 `A` 类，`JIAO` 命名空间中也有一个 `A` 类。
前者实例化后输出 666，后者实例化后输出 777。

```cpp
#include <iostream>

namespace jiao {
class A{
public:
    void print(){
        std::cout<<"666";
    }
};
}

namespace JIAO {
class A{
public:
    void print(){
        std::cout<<"777";
    }
};
}

int main(){
    jiao::A a1;
    JIAO::A a2;
    a1.print(); // 输出 666
    a2.print(); // 输出 777
    return 0;
}
```

<br>

## 命名空间的嵌套

命名空间允许嵌套。

```cpp
#include <iostream>

namespace JIAO{
void p(){
    std::cout<<"555";
}

namespace jiao1{
    void p(){
        std::cout<<"666";
    }
}

namespace jiao2{
    void p(){
        std::cout<<"777";
    }
}
}

int main(){
    JIAO::p();
    JIAO::jiao1::p();
    JIAO::jiao2::p();
    return 0;
}
```

<br>

## 命名空间和类的区别

对于类而言：`A` 类中可以有 `p` 函数，`B` 类中可以有 `p` 函数；
对于命名空间而言，`A` 命名空间中可以有 `p` 函数，`B` 命名空间中也可以有 `p` 函数。
这俩值得比较一下：

| 维度 | 命名空间 | 类 |
|:-:|:-:|:-:|
| 实例化 | 不需要实例化，直接访问命名空间中的成员 | 需要实例化对象，通过对象访问类的成员 |
| 封装性 | 不具备封装性，命名空间中的成员默认是公有的 | 具有封装性，类的成员可以是公有的、私有的、或受保护的 | 
| 内存管理 | 不需要内存管理，命名空间中的成员都是静态的 | 需要内存管理，类的成员可以是静态的、也可以是动态的 |
| 适用场景 | 用于组织代码、避免命名冲突 | 用于封装数据和行为、实现面向对象编程 |

> Q：为什么命名空间中的成员都是静态的？

> A：因为命名空间中的成员都是全局的，全局的成员都是静态的。
> 因此，即使类定义在命名空间中，但实际的内存分配和释放是与类的实例化相关的，而不是与命名空间本身相关。

<br>

## 关于 cstdio 和 stdio.h
 
`cstdio` 是 C++ 标准库的头文件，其中定义了 C 语言标准库的函数，这些函数被放置在 std 命名空间中。因此，在 C++ 中使用 `cstdio` 时，需要加上 `std::` 前缀，例如 `std::printf`、`std::fopen`等。

`stdio.h` 是 C 语言标准库的头文件，其中定义了 C 语言标准库的函数，这些函数被放置在全局命名空间中。因此，在 C 语言中使用 `stdio.h` 时，不需要加上 `std::` 前缀，例如 `printf`、`fopen`等。

**但是**，为了保持语言的向后兼容性，这些标准库函数也可以直接在全局作用域（即不加 `std::` 前缀）中使用，而不会产生编译错误。这是一个历史遗留的特性，但不是推荐的做法，更推荐使用 `std::printf` 等带有 `std::` 前缀的形式，以确保代码的清晰性和可读性，避免潜在的命名冲突问题。

<br>

在这段代码中，我们定义了一个命名空间 `jiao`，其中有一个 `printf` 函数，输出 `666`。
在 `main` 函数中，我们调用了 `jiao` 命名空间中的 `printf` 函数，输出 `666`，
调用标准库中的 `std::printf` 函数，输出 `777`。

```cpp
#include <iostream>
#include <cstdio>

namespace jiao{
    void printf(){
        std::cout<<"666";
    };
}

int main(){
    jiao::printf();     // 666
    std::printf("777"); // 777
    return 0;
}
```

<br>

在这段代码中，我们没有引入 `std` 命名空间，所以 `std::printf` 会报错。

```cpp
//#include <iostream>   // iostream 会引入 std::printf
#include <stdio.h>      // 非cstdio，没有引入 std 的概念

namespace jiao{
    void printf(){
        //std::cout<<"666";
    };
}

int main(){
    jiao::printf();
    printf("777");
    std::printf("888"); // 命名空间 "std" 中没有 "printf"
    return 0;
}
```

<br>

---

# string 


> **备忘**
> ```cpp
> // i2s
> s = std::to_string(i);
> ```
> ```cpp
> // s2i
> i = std::stoll(s);
> ```

字符串常常会有这几个头文件：

```cpp
#include <string>
#include <string.h>
#include <cstring>
```

对于 `string.h` 和 `cstring`，本质上都是 C 语言中的头文件。
`cstring` 相较于 `string.h`，多了一个命名空间。
因此，我们只讨论 `string` 和 `cstring`。

## string

`string` 操作的是 C++ 中的字符串，也就是 `std::string`。

**值得一提** 的是，我们往往不需要引入 `string` 头文件，因为 `string` 头文件已经被 `iostream` 引入了。

`string` 是一个类，所以它有构造函数、析构函数、拷贝构造函数、赋值运算符等等。

<br>

* 构造函数

```cpp
string s1;          // 默认构造函数，s1 为空字符串
string s2(s1);      // 拷贝构造函数，s2 为 s1 的拷贝
string s3("hello"); // 用字符串初始化 s3
string s4(10, 'a'); // 用 10 个 'a' 初始化 s4
```

* 赋值运算符

```cpp
string s1, s2;
s1 = s2;            // s1 为 s2 的拷贝
string s3 = "hello";
s1 = s3;            // s1 为 s3 的拷贝
```

* 比较运算符

先按字典序比较，如果相等，再比较长度。

```cpp
string a = "aa";
string b = "ab";
a < b;  // true 
```

```cpp
string a = "bb";
string b = "bba";
a < b;  // true 
```

* 插入元素

```cpp
string s = "hello";
s.insert(1, "6");   
// 将 6 插入到 s 下标为 1 的位置
// 输出 h6ello
```

* 删除元素

```cpp
string s = "hello";
s.erase(0, 2);      
// 将 s 下标为 0 的字符开始的 2 个字符删除
// 输出 llo
```

* 替换元素

```cpp
string s = "hello";
s.replace(0, 2, "6");   
// 将 s 下标为 0 的字符开始的 2 个字符替换为 6
// 输出 6llo
```

* 查找元素

```cpp
string s = "hello";
int idx = s.find("ll"); 
// 查找 s 中第一个 "ll" 的位置，返回目标字符串的第一个字符的下标
// 输出 2
```

* 获取子串

```cpp
string s = "hello";
s.substr(2, 2);     
// 获取 s 中下标为 2 的字符开始的 2 个字符
// 输出 ll
```

* 获取长度

```cpp
string s = "hello";
s.size();           
// 获取 s 的长度
// 输出 5
```

* 转换为 C 风格字符串

```cpp
string s = "hello";
s.c_str();          
// 将 s 转换为 C 风格字符串
```

* 转换为整数

```cpp
string s = "123";
stoi(s);            // 将 s 转换为整数
stoll(s);           // 将 s 转换为长整数
```

* 转换为双精度浮点数

```cpp
string s = "123.456";
stod(s);            // 将 s 转换为双精度浮点数
```

<br>

## cstring

`cstring` 操作的是 C 风格的字符串，也就是以 `\0` 结尾的字符数组。

C 风格的字符串有三种写法：

```cpp
int main(){
    char str1[6] = "hello";
    char str2[] = "hello";
    char *str3 = "hello";
}
```

* `str1` 
    此写法会在 `str1[5]` 的位置插入 `\0`。
    数据保存在栈中。

* `str2`
    编译器会自动将 `str2` 的长度设置为 6，且在 `str2[5]` 的位置插入 `\0`。
    数据保存在栈中。

* `str3`
    此写法会在常量区（常量区不可更改）创建一个字符串，然后将 `str3` 指向该字符串的首地址。
    数据保存在常量区，**`str3` 本身** 保存在栈中。

显然，`str1` 和 `str2` 是等价的。我们都知道，数组名其实是一个指针，
所以 `str1` 和 `str2` 都是指向栈中的一个字符串。而 `str3` 则是指向常量区的一个字符串。

```cpp
// 输出地址
for(int i = 0; i < 6; i++) 
    printf("%x %x\n", str1 + i, &str1[i]);
// 输出内容
for(int i = 0; i < 6; i++)
    printf("%c %c\n", *(str1 + i), str1[i]);
```

```
19d5f2ec 19d5f2ec
19d5f2ed 19d5f2ed
19d5f2ee 19d5f2ee
19d5f2ef 19d5f2ef
19d5f2f0 19d5f2f0
19d5f2f1 19d5f2f1
h h
e e
l l
l l
o o
NUL NUL
```

如果把 `str3` 指向 `str1`，即 `str3 = str1`，那么 `str3` 就指向了栈中的一个字符串。
紧接着，将上面的代码复制，换成 `str3`，输出结果一毛一样。

**这就是 C 风格的字符串。本质上都是指针，指向一个连续的内存空间。**

[菜鸟教程](https://www.runoob.com/cprogramming/c-standard-library-string-h.html) 详细介绍了 `cstring` 的用法，下面是一些常用的函数：

<br>

* `strlen` 获取字符串长度 `size_t strlen(const char *s);`

```cpp
unsigned int len = strlen(str);
```

`strlen` 计算从 `str` 开始，到 `\0` 结束的长度。
所以，如果 `str` 中间有 `\0`，那么 `strlen` 只会返回到 `\0` 的长度。

容易混淆的是，`sizeof` 的功能是计算一个数据类型的大小，这个类型可以是数组、函数、指针、对象等，单位为字节。

* `memset` 设置字符串内容 `void *memset(void *s, int c, size_t n);`

```cpp
memset(str, 'a', sizeof str);
```

`memset` 按字节对 `str` 进行初始化，`sizeof str` 为 `str` 的大小，单位为字节。
值得一提的是，`memset` 的第二个参数是 `int` 类型，但是实际上只会取 `char` 的低 8 位。 

在算法竞赛中，我们常常会使用 `memset(g, 0x3f, sizeof g)` 来初始化一个数组。
实际上，`0x3f` 的二进制为 `0011 1111`。`memset` 会将 `g` 的每个字节都设置为 `0011 1111`。
假设 `g` 的类型为 `int`，一个 `int`，4 个字节，那么 `g` 中每个元素

* 二进制为 `0011 1111 0011 1111 0011 1111 0011 1111`。
* 十进制为 `1061109567`。


```cpp
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
int strcmp(const char *s1, const char *s2);
char *strchr(const char *s, int c);
char *strstr(const char *haystack, const char *needle);
void *memcpy(void *dest, const void *src, size_t n);
```


<br>

---

# stream

流，C++ 中的一种抽象概念，用于表示数据在程序和外部设备（如文件、键盘、屏幕等）之间的流动。

* **缓冲区**：缓冲区是一个临时存储区域，用于存放输入输出的数据。
    用于减少对输入输出设备的访问次数，从而提高效率。（缓冲区更快，输入输出设备更慢）
* **状态**：流具有不同状态：
    * `good()`：流正常。
    * `bad()`：流崩溃。
    * `fail()`：流操作失败。
    * `eof()`：流到达文件末尾。

    ```cpp
    if(std::cin.good()) std::cout << "good" << std::endl;
    ```

## io stream

`iostream`：标准输入输出流，用于控制台输入输出。

```cpp
std::cin >> x;    // 从控制台输入
std::cout << x ;  // 输出到控制台
```


* 读入
    ```cpp
    // 100 a
    int a;
    char c;
    ```

    * `cin`
        ```cpp
        std::cin >> a >> c;
        ```
        正确读入，`a = 100`，`c = 'a'`。
    * `scanf`
        ```cpp
        scanf("%d%c", &a, &c);
        ```
        不符合预期，`a = 100`，`c = ' '`。

* 输出
    * `endl`
        ```cpp
        std::cout << a << std::endl;
        ```
        输出 `a` 并换行，同时刷新缓冲区。

        ```cpp
        #include <iostream>
    
        int main(){
            // 立即输出
            std::cout << "hello" << std::endl;
            // 程序自动判断何时输出
            std::cout << "world";

            while(1);
            return 0;
        }
        ```
    
    * `flush`
        ```cpp
        std::cout << a << std::flush;
        std::flush(std::cout);
        ```
        输出 `a`，但不换行，同时刷新缓冲区。

    * 关闭 C / C++ 的输入输出同步
        ```cpp
        std::ios::sync_with_stdio(false);        
        ```
        * 关闭之后，`cin` 和 `scanf` 的输入顺序不再保证一致。
    
    * 关闭缓冲区
        ```cpp
        std::cin.tie(nullptr); std::cout.tie(nullptr);
        ```
        * 理论上，关闭之后，`cin` 和 `cout` 不再绑定，`cin` 的输入不会刷新 `cout` 的输出。
                

### iomanip

* `setw` 设置字段宽度
    ```cpp
    std::cout << std::setw(5) << 123 << std::endl;
    // "  123"
    ```

* `setfill` 设置填充字符
    ```cpp
    std::cout << std::setw(5) << std::setfill('G') << 123 << std::endl;
    // "GG123"
    ```

* `fixed` `setprecision` 设置浮点数的小数精度
    ```cpp
    std::cout << std::setw(5) << std::fixed << std::setprecision(2) << 3.1415926 << std::endl;
    // " 3.14"
    ```

* `left` `right` 控制字段中数据的对齐方式
    ```cpp
    std::cout << std::setw(5) << std::left << 123 << std::endl;
    // "123  "
    ```

### cerr

`cerr`：标准错误流，立即输出到控制台，不会缓冲。

```cpp
std::cerr << "error" << std::endl;
```

## f stream

`fstream`：文件输入输出流，用于文件输入输出。

### ifstream

从文件读入数据。
    
1. 打开文件
```cpp
std::ifstream ifs("in.txt");
    
if(!ifs.is_open()){
    std::cerr << "打开文件失败" << std::endl;
    return 1;
}
```

2. 读取文件

* 按 `\n` 读取
    ```cpp
    std::string s;
    while(std::getline(ifs, s))
        std::cout << s << std::endl;
    ```

* 按 ` ` 读取

    ```cpp
    std::string s;
    while(ifs >> s)
        std::cout << s << std::endl;
    ```

3. 移动文件指针

    ```cpp
    ifs.seekg(0, std::ios::beg);    // 移动到文件开头
    ```

    > 移动文件指针还有更多用法。详见 [cppreference](https://zh.cppreference.com/w/cpp/io/basic_istream/seekg)。


3. 关闭文件

    ```cpp
    ifs.close();
    ```

### ofstream

1. 打开文件
    ```cpp
    std::ofstream ofs("out.txt");
    ```

2. 写入文件

    ```cpp
    ofs << "hello" << std::endl;
    ```

3. 关闭文件

    ```cpp
    ofs.close();
    ```

## s stream

`sstream`：字符串输入输出流。提供一种灵活的方式，将字符串当作流来处理。

* 初始化

    ```cpp
    std::stringstream ss;
    ```

* 写入

    ```cpp
    ss << "hello";
    ss << 123;
    ss << 3.14;
    ```

* 读取

    ```cpp
    std::string s;
    int a;
    double b;

    ss >> s >> a >> b;
    ```

* 进制转换

    * `dec` -> `oct` / `hex`
        ```cpp
        std::stringstream ss;
        std::string s;
        int num = 666;

        // 将 num 以八进制形式写入 ss
        ss << std::oct << num;
        ss >> s;
        std::cout << s << std::endl;// 1232

        ss.clear();

        // 将 num 以十六进制形式写入 ss
        ss << std::hex << num;
        ss >> s;
        std::cout << s << std::endl;// 29a
        ```
    
    * `oct` / `hex` -> `dec`
        ```cpp
        std::string a = "1232";
        std::string b = "29a";
        int num;

        num = std::stoi(a, nullptr, 8);
        std::cout << num << std::endl;  // 666
        
        num = std::stoi(b, nullptr, 16);
        std::cout << num << std::endl;  // 666
        ```

<br>

---

# bitset

处理二进制位的类，提供了一系列成员函数来执行位操作。
在 `bitset` 中，数据保存形如数组。

## 创建

```cpp
bitset<4> b1;       // 长度为 4：0000
bitset<8> b2(5);    // 长度为 8：0000 0101
bitset<8> b3("101");// 长度为 8：0000 0101

b1.reset();         // 全部置 0
b1.set();           // 全部置 1
b1.set(i);          // i 位置 1
b1.set(i, 0);       // i 位置 0
```

## 转换

```cpp
string a = b1.to_string();
unsigned long long b = b1.to_ullong();
```

## 位操作

```cpp
bitset<4> b1("1100");
bitset<4> b2("1001");

// 按位取反
cout << ~b1 << endl;        // 0011
// 按位与
cout << (b1 & b2) << endl;  // 1000
// 按位或
cout << (b1 | b2) << endl;  // 1101
// 按位异或
cout << (b1 ^ b2) << endl;  // 0101
// 右移
cout << (b2 >> 2) << endl;  // 0010
// 左移
cout << (b2 << 2) << endl;  // 0100

// 某一位取反
b1.flip(i);
```

## 成员函数

```cpp
bitset<16> b1(6666);    // 0001 1010 0000 1010

// 使用 [] 输出
for(int i=b1.size()-1; i>=0; i--) cout<<b1[i];
cout<<endl;

// 统计二进制中 1 的个数
cout<<b1.count()<<endl; // 5
// 求bitset的大小
cout<<b1.size()<<endl;  // 16
// 判断某位（从右到左，下标从 0 开始）是否为 1
cout<<b1.test(9)<<endl; // true

// 判断是否全为 0
cout<<b1.none()<<endl;  // 0
// 判断是否全为 1
cout<<b1.all()<<endl;   // 0
// 判断是否有 1
cout<<b1.any()<<endl;   // 1
```




<br>

---

# regex

[正则表达式](/Linux/Regex/index.html) 的本质，就是某种 **字符组合**。 

## 定义正则表达式

```cpp
std::regex r(R"((\d{1,3}\.){3}\d{1,3})");
```

## 判断串

用于判断整个字符串是否匹配正则表达式。

```cpp
std::regex_match("127.0.0.1", r);   // true
std::regex_match("a127.0.0.1", r);  // false
```

## 查找 / 取出匹配子串

用于查找字符串中匹配正则表达式的子串。

1. 使用 `std::sregex_iterator`

C++ 中用于处理正则表达式匹配结果的迭代器类。

```cpp
for(auto i=std::sregex_iterator(s.begin(), s.end(), r); i!=std::sregex_iterator(); i++)
    std::cout << (*i).str() << std::endl;
```

2. 使用 `std::regex_search`

```cpp
std::smatch matches;
while (std::regex_search(s, matches, r)) {
    std::cout << matches.str() << std::endl;
    s = matches.suffix().str(); // 获取当前匹配子串之后的子串
}
```

## 替换匹配子串

替换所有匹配子串：

```cpp
// 将 s 中所有匹配 r 的子串替换为 "666"，保存到 ss 中
std::string ss = std::regex_replace(s, r, "sss");
```

替换第一个匹配子串：

```cpp
// 将 s 中第一个匹配 r 的子串替换为 "666"，保存到 ss 中
std::string ss = std::regex_replace(s, r, "666", std::regex_constants::format_first_only);
```


<br>

---

# template

template：变参数模板。

## 在函数中使用 template

可以让函数接受任意类型的参数，而不是固定的类型。


```cpp
template<typename T>
void Tswap(T *a, T *b){
    T temp = *a;
    *a = *b;
    *b = temp;
}
```

## 在类中使用 template

可以让类接受任意类型的参数，而不是固定的类型。

```cpp
template<typename T>
class queue {
public:
    void push(T x){
        q[tail++] = x;
    };
    void pop(){
        head++;
    };
    T front(){
        return q[head];
    };
    int size(){
        return this->tail-this->head;
    }
private:
    T q[100];
    int head = 0;
    int tail = 0;
};
```

## variant

基于模板的类型安全联合。

```cpp
#include <variant>
```

```cpp
std::variant<int, double, std::string> uids;
```

输出之前，需要检查类型是否符合预期。

```cpp
uids = 123;
uids = 3.14;
uids = "Hello_world!";

if(std::holds_alternative<int>(uids))
    std::cout << std::get<int>(uids) << std::endl;
else
    // 错误处理
```

<br>

---

# functional

## lambda

lambda：匿名函数 / 闭包。

允许在需要函数对象（比如传递给算法、STL 容器等）的地方，以一种更为简洁的方式定义匿名函数。

```cpp
[capture](parameters) -> return_type { body_of_lambda }
```

* capture：捕获列表，捕获外部变量。
* parameters：参数列表。
* return_type：返回值类型。
* body_of_lambda：函数体。

```cpp
#include <iostream>

int main() {
    int x=1;
    int y=2;
     
    // 使用Lambda表达式直接定义并调用
    // Lambda捕获x, y变量，并传递参数x+y, y*y
    int result = 
        [x, y](int a, int b) -> int {
            return x + y + a + b;
        }(x+y, y*y); 
    
    std::cout << "Result: " << result << std::endl; // 输出 10
    
    return 0;
}
```

```cpp
#include <iostream>
#include <functional>

int main() {
    int x=1;
    int y=2;
    
    std::function<int(int, int)> f = [x, y](int a, int b) -> int{
        return x + y + a + b;
    };

    std::cout << f(x*x, y+y) << std::endl;

    return 0;
}
```

<br>

---


## function

function：用来包装任何可以被调用的对象，包括函数指针、函数对象、Lambda 表达式、成员函数指针等，从而提供了一种统一的方式来处理各种可调用对象。

```cpp
#include <functional>
std::function<return_type(parameter_types)> function_name;
```

* return_type：返回值类型。
* parameter_types：参数类型。
* function_name：函数名。

**使用成员函数指针**

```cpp
#include <iostream>
#include <functional>

class MyClass {
public:
    int multiply(int a, int b) {
        return a * b;
    }
};

int main() {
    MyClass obj;
    std::function<int(MyClass&, int, int)> func = &MyClass::multiply;
    std::cout << func(obj, 3, 4) << std::endl;  // 输出 12
    
    return 0;
}
```

**使用函数指针**

```cpp
#include <iostream>
#include <functional>

int add(int a, int b) {
    return a + b;
}

int main() {
    std::function<int(int, int)> func = add;
    std::cout << func(3, 4) << std::endl;  // 输出 7
    
    return 0;
}
```

<br>

---

# 移动语义和右值引用

<br>

---

# 智能指针

为了解决内存泄漏、野（wild）指针、悬空（dangling）指针的问题，引入了智能指针。

```cpp
#include <memory>
// unique_ptr
// shared_ptr
// weak_ptr
```

**内存泄漏**

导致内存占用过多，程序崩溃。
* 程序运行时，申请的内存没有被释放。无法再次使用该内存。
* 丢失了指向该内存的指针。无法访问、释放该内存。

**野指针**

当一个指针未被显式初始化，它的值就是未知的，可能是一个随机的内存地址，也可能是特定编译环境下的默认值（通常是0或者nullptr）

**悬空指针**

指向的内存已经被释放，但是指针本身没有被释放。

* 释放内存后，指针没有被置为 nullptr。
```cpp
int *ptr = new int; // 申请内存
delete ptr;         // 释放内存
// ptr 已经悬空
ptr = nullptr;      // 将 ptr 置为 nullptr, ptr 成空指针
```

* 在函数中返回局部变量的指针。

```cpp
int *func(){
    int a = 6;      // 局部变量
    return &a;      // 返回局部变量的指针
}
int *ptr = func();  // ptr 指向的内存已经被释放
// ptr 已经悬空
```

* 在函数中返回指向堆内存的指针，但是没有释放堆内存。

```cpp
int *func(){
    int *ptr = new int; // 申请内存
    return ptr;         // 返回指向堆内存的指针
}
int *ptr = func();      // ptr 指向的内存没有被释放
delete ptr;             // 释放内存
// ptr 已经悬空
ptr = nullptr;          // 将 ptr 置为 nullptr, ptr 成空指针
```


## unique_ptr

**独占所有权**：当 `unique_ptr` 被销毁时，它所指向的对象也被销毁。

```cpp
void func(){
    std::unique_ptr<int> ptr = std::make_unique<int>(666);
}
// 当函数结束时，ptr 被销毁，ptr 指向的内存也被销毁
// 也可以手动销毁
ptr.reset();        // 销毁 ptr 指向的内存
ptr.reset(nullptr); // 销毁 ptr 指向的内存（等价）
```

## shared_ptr

**共享所有权**：多个 `shared_ptr` 可以指向同一个对象，当最后一个 `shared_ptr` 被销毁时（引用记数为 0 的时候），它所指向的对象也被销毁。

```cpp
#include <iostream>
#include <memory>

// 通过引用传递智能指针
// p1 和 p2 指向同一个对象，引用计数为2
void f2(std::shared_ptr<int> &p1){
    std::shared_ptr<int> p2 = std::make_shared<int>(666);
    p1=p2;
    // 此时p2和p1指向同一个对象，引用计数为2
    std::cout<<p1.use_count()<<std::endl;
}

// 创建一个空的智能指针，通过引用传递给f2函数
void f1(){
    std::shared_ptr<int> p1;
    f2(p1);
    // 当f2函数执行完毕后，f2函数内部的p2指针被销毁，引用计数为1
    std::cout<<p1.use_count()<<std::endl;
    std::cout << *p1 << std::endl;
}

int main(){
    f1();
    return 0;
}
```


## weak_ptr

为了避免 `shared_ptr` 的循环引用问题，引入了 `weak_ptr`。

todo

<br>

---

# 异常处理

异常指的是程序运行时发生的错误，比如除零错误、数组越界等。

## try catch throw

* `try`
    将可能引发异常的一个或多个语句封闭起来。
    
    ```cpp
    try{
        // 可能引发异常的语句
        throw;  // 抛出异常
    }catch(...){
        // 异常处理
        throw;  // 重新抛出异常
    }
    ```


* `catch`
    捕获异常，处理异常。

* `throw`
    抛出异常。



## RAII

RAII（Resource Acquisition Is Initialization）：资源获取即初始化。

RAII 的核心思想是，将资源的生命周期与对象的生命周期绑定，通过对象的析构函数来释放资源。

RAII 是 C++ 中常用的一种资源管理方式，也是智能指针的基本原理。

```cpp
#include <iostream>
#include <fstream>
#include <memory>

class File{
public:
    File(const std::string& filename): _filename(filename){
        // 文件可读写可追加，不存在则创建
        _fs = std::make_unique<std::fstream>(_filename, std::ios::in | std::ios::out | std::ios::app);
        // 打开失败
        if(!_fs->is_open())
            throw std::runtime_error("文件" + _filename + "打开失败!");
    };

    // 析构函数
    ~File(){};

    // 读取文件
    void read(){
        _fs->seekg(0, std::ios::beg);   // 定位到文件头
        std::string line;
        while(getline(*_fs, line))
            std::cout << line << std::endl;
        
        if(!_fs->eof())
            throw std::runtime_error("读取" + _filename + "失败!");
    }

    // 写入文件
    void write(const std::string& line){
        *_fs << line;
        
        if(!_fs->good())
            throw std::runtime_error("写入" + _filename + "失败!");
    }

private:
    std::string _filename;
    std::unique_ptr<std::fstream> _fs;
};

int main(){
    try{
        File f("t.txt");
        f.write("hello world\n");
        f.read();
    }catch(const std::exception& e){
        // 尝试修复
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
```


## 断言

断言（Assertion）是在编程中用于检查程序运行时是否满足特定条件的一种方法。它是一种用于验证程序假设是否正确的声明，通常在开发和调试阶段使用。


```cpp
#include <cassert>
#include <iostream>

int main(){
    int x = 10;
    assert(x < 10); // 如果x >= 10，程序会终止
    std::cout<<x<<std::endl;
    return 0;
}
```

如果在编译时定义了 `NDEBUG`，那么 `assert` 会被忽略。

```cpp
#define NDEBUG
```

<br>

---


# STL

**jiao 的 [CPP_STL](https://github.com/daixll/CPP_STL)**

STL（standard template library），泛型库。
提供了一系列的模板类和模板函数，支持常用的数据结构和算法。

## 如果你未曾接触过数据结构

我们简单考虑一下，这个数组：

```cpp
int a[666];
```

首先明确：

* 当我们声明一个数组时，系统会为我们分配一段 **连续** 的内存空间。
* 而数组的名字，就是这段内存空间的 **首地址**，这段空间的 **第一个** 元素。
    * 访问某地址上的数据，需要解引用，即 `*a`。
* 显然，如果我们想访问数组的第 **2** 个元素，地址是 `a+1`，即 `*(a+1)`。
    * 我们常用的 `a[i]`，其实就是 `*(a+i)`。

因此，总结一下其优缺点：

**优点**：

1. 可以通过下标（偏移量）访问元素，时间复杂度为 `O(1)`。

**缺点**：

1. 因为声明时就分配了内存空间，所以数组的大小是 **固定** 的。
2. 我们无法在数组中间插入（删除）元素，因为这会破坏数组的连续性。
    * 除非我们将目标 **后** 的元素全部后移（前移），然后再插入（删除）。

> 人生如戏，我们无法提前知晓它的篇幅，也不知其何时谢幕。
> 戏如人生，有人在某个瞬间无奈离去，而也有新的面孔在不经意间加入。

为了能够在数组中间插入（删除）元素，肯定需要摆脱数组的 **连续性**，我们知道，数组中间的元素，是通过第一个元素的地址加上偏移量来访问的，一旦这个连续性被打破，我们就无法通过偏移量来访问元素了。

因此，单向链表就应运而生了。


## 迭代器 iterator

迭代器是一种泛型指针，它可以指向容器中的元素。

```cpp
容器::iterator it;
```

具体的：

```cpp
vector<int>::iterator it;
unordered_multimap<int, int>::iterator it;
```

### 迭代器的类型

* `iterator`：普通迭代器。
* `const_iterator`：常量迭代器，只能读取，不能修改。
* `reverse_iterator`：反向迭代器，从后往前遍历。
* `const_reverse_iterator`：常量反向迭代器，从后往前遍历，只能读取，不能修改。

> 反向迭代器只能用于支持双向迭代器的容器，`unordered` 系列容器不支持反向迭代器。

### 获取迭代器

容器拥有 `begin` 和 `end` 成员函数，用于获取迭代器：

* `begin()`：指向容器第一个元素，正向迭代。
* `cbegin()`：指向容器第一个元素，且只能读取，不能修改。
* `rbegin()`：指向容器最后一个元素，反向迭代。
* `crbegin()`：指向容器最后一个元素，且只能读取，不能修改。

<br>

* `end()`：指向容器最后一个元素的 **下一个** 位置，正向迭代。
* `cend()`：指向容器最后一个元素的 **下一个** 位置，且只能读取，不能修改。
* `rend()`：指向容器第一个元素的 **前一个** 位置，反向迭代。
* `crend()`：指向容器第一个元素的 **前一个** 位置，且只能读取，不能修改。

### 操作迭代器

* `*it`：获取迭代器指向的元素。
    特别的，访问元素的成员变量时 `(*it).first`，可以简写为 `it->first`。
* `it++`：迭代器后移。
* `it--`：迭代器前移。

### 范围 for 循环

在 `for` 循环中，使用迭代器遍历容器。

```cpp
for(int i: v)
    cout<<i<<" ";
// i 为 v 中的每个元素
// 常常简写为
for(auto i: v)
    cout<<i<<" ";
```

<br>

---


## 序列式容器

所谓序列式容器，其中的元素 **可序**，但未必 **有序**。

<br>

---

### 【随机】vector

动态数组，支持自动扩容。
内存空间是连续的，所以支持随机访问，
故其迭代器是随机访问迭代器。

#### 创建

```cpp
vector<int> v1;             // 空数组
vector<int> v2(10);         // 10个元素，每个元素都是0
vector<int> v3(10, 1);      // 10个元素，每个元素都是1
vector<int> v4(v3);         // 拷贝构造函数
vector<int> v5({1, 2, 3, 4, 5}); // 初始化列表
```

#### 增加

```cpp
v1.push_back(6);            // 尾部插入
v1.emplace_back(6);         // 尾部插入

v1.insert(v1.begin(), 6);                   // 插在 v1.begin() 之前，即头部插入
v1.insert(v1.begin(), 10, 6);               // 插在 v1.begin() 之前，即头部插入10个6
v1.insert(v1.begin(), v2.begin(), v2.end());// 插入 v2 的所有元素
v1.insert(v1.begin(), {1, 2, 3, 4, 5});     // 插入初始化列表

v1.emplace(v1.end(), 6);                    // 插在 v1.end() 之前，即尾部插入
v1.emplace(v1.end(), 10, 6);                // 插在 v1.end() 之前，即尾部插入10个6
v1.emplace(v1.end(), v2.begin(), v2.end()); // 插入 v2 的所有元素
v1.emplace(v1.end(), {1, 2, 3, 4, 5});      // 插入初始化列表
```

> `emplace` 函数的参数是构造函数的参数，而 `insert` 函数的参数是元素的值。
>   ```cpp
>   v1.push_back(10)
>   v1.emplace_back(10)
>   ```
>  上面两行代码的效果是一样的，都是在 `v1` 的尾部插入一个值为 `10` 的元素。
>   * `push_back`：先在内存中构造一个 `10`，然后将其拷贝到 `v1` 的尾部。
>   * `emplace_back`：直接在 `v1` 的尾部构造一个 `10`。

#### 删除

```cpp
v1.clear();                 // 清空数组

v1.pop_back();              // 尾部删除
v1.erase(v1.begin());       // 删除 v1.begin() 位置的元素
v1.erase(v1.begin(), v1.end()); // 删除 [v1.begin(), v1.end()) 之间的元素
```

#### 修改

```cpp
v1[1] = 6;                  // 将下标为 1 的元素改为 6
v1.at(1) = 6;               // 将下标为 1 的元素改为 6 (越界会抛出异常)

std::vector<int>::iterator it = v1.begin();
*it = 6;                    // 将 it 指向的元素改为 6
```

```cpp
// 重新分配元素
v1.assign(10, 6);            // 数组大小改为10，所有元素都是6
v1.assign(v2.begin(), v2.end()); // 拷贝 v2 的所有元素
v1.assign({1, 2, 3, 4, 5});  // 拷贝初始化列表

// 更改容器大小
v1.resize(10);              // 数组大小改为10，多余的元素被删除，不足的元素被补 0
v1.resize(10, 6);           // 数组大小改为10，多余的元素被删除，不足的元素被补 6
```

#### 查找

```cpp
// v1.find
auto it = v1.find(6);       // 查找第一个值为 6 的元素，返回迭代器
if(it != v1.end())          // 找不到时，it == v1.end()
    cout<<*it<<endl;        // 输出 6

// 通过迭代器遍历
auto it = v.begin();
while(it != v.end()){
    cout<<*it<<" ";
    it++;
}
// 通过 for 循环遍历
for(auto i: v) cout<<i<<" ";

v1.empty();                 // 判断数组是否为空
v1.size();                  // 返回数组大小
v1.max_size();              // 返回数组最大容量

v1.front();                 // 返回头部元素
v1.back();                  // 返回尾部元素

v1[0];                      // 返回下标为 0 的元素
v1.at(0);                   // 返回下标为 0 的元素 (越界会抛出异常)

v1.data();                  // 返回第一个元素的指针
```

#### 其他

```cpp
v1.capacity();              // 返回数组容量
v1.shrink_to_fit();         // 释放多余的空间
v1.reserve(10);             // 预留 10 个元素的空间，避免多次扩容
```

<br>

---

### 【随机】deque

```cpp
#include <queue>            // deque 头文件
```

在 `vector` 的基础上，增加了在头部插入和删除元素的操作。
然后，这个东西就叫做 **双端队列** 了。

```cpp
dq.push_front(6);           // 头部插入
dq.emplace_front(6);        // 头部插入
dq.pop_front();             // 头部删除
```

<br>

---

### 【随机】array

固定大小的数组，连续的内存空间，支持随机访问。
因为固定大小，所以不支持插入和删除操作，只能修改元素。

#### 创建

```cpp
array<int, 5> a1;                   // 5个元素，每个元素都是0
array<int, 5> a3 = {1, 2, 3, 4, 5}; // 初始化列表

// 使用迭代器
array<int, 5>::iterator it = a1.begin();
```




<br>

---

### list

双向链表。
内存空间不是连续的，所以不支持随机访问，故其迭代器是双向迭代器。
因为不支持随机访问，若想要访问下标为 `i` 的元素，只能从头部开始遍历，直到遍历到下标为 `i` 的元素（或者从尾部开始遍历）。

### forward_list

单向链表。
相较于 `list`，`forward_list` 只能从头部开始遍历，不能从尾部开始遍历。
也不支持 `size()` 函数，所以不能获取链表的大小。
也不支持 `push_back()` 函数，所以不能在尾部插入元素。
支持头部插入元素，所以有 `push_front()` 函数。这也意味着，`forward_list` 是带有头结点的链表。

#### 增加

```cpp
fl1.push_front(0);					// 头部插入
fl1.emplace_front(-1);				// 头部插入
fl1.pop_front();					// 头部删除

fl1.insert_after(fl1.begin(), 10);	// 在指定位置后插入
fl1.emplace_after(fl1.begin(), 20); // 在指定位置后插入
fl1.erase_after(fl1.begin());		// 在指定位置后删除
```

<details><summary>单链表（C实现）</summary>

```cpp
#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	node *next;

	void insert_after(int x){
		node *t = (node*)malloc(sizeof(node));	// 申请新的节点
		t->data = x;	// 新节点的数据域存放 x
		t->next = next;	// 新节点的 next 指向当前节点的 next

		next = t;		// 当前节点的 next 指向新节点
	}

	void delete_after(){
		node *t = next;	// t 指向当前节点的下一个节点
		next = t->next;	// 当前节点的 next 指向 t 的下一个节点
		free(t);		// 释放 t
	}
};

int main(){
	node *head = (node*)malloc(sizeof(node));
	head->data = 0;		// 头节点的数据域不存放数据，用来存放链表的长度
	head->next = NULL;	// 头节点的 next 指向 NULL

	node *p = head;
	for(int i = 1; i <= 10; i++){
		p->insert_after(i);
		p = p->next;
	}

	printf("链表：\n");
	for(p = head->next; p != NULL; p = p->next) printf("%d ", p->data);
	
	p = head;
	p = p->next; p = p->next;
	p->delete_after();
	p->delete_after();

	printf("\n删除第3、4个元素后的链表：\n");
	for(p = head->next; p != NULL; p = p->next) printf("%d ", p->data);
	
	return 0;
}
```
</details>




<br>

---




### 【-】stack

栈

#### 创建

```cpp
stack<int> s1;              // 空栈
stack<int> s2(s1);          // 拷贝构造函数
stack<int> s3({1,2,3});     // 初始化列表，1为栈底，3为栈顶
```

#### 增加

```cpp
s1.push(6);                 // 入栈
```

#### 删除

```cpp
s1.pop();                   // 出栈
```

#### 修改

只能通过入栈和出栈来修改栈。

#### 查找

```cpp
// 遍历栈 会清空栈
while(!s1.empty()){
    cout<<s1.top()<<" ";
    s1.pop();
}

s1.empty();                 // 判断栈是否为空
s1.size();                  // 返回栈大小
s1.top();                   // 返回栈顶元素
```

<br>

---

### 【-】queue

队列

#### 创建

```cpp
queue<int> q1;              // 空队列
queue<int> q2(q1);          // 拷贝构造函数
queue<int> q3({1,2,3});     // 初始化列表，1为队头，3为队尾
```

#### 增加

```cpp
q1.push(6);                 // 入队
```

#### 删除

```cpp
q1.pop();                   // 出队
```

#### 修改

只能通过入队和出队来修改队列。

#### 查找

```cpp
// 遍历队列 会清空队列
while(!q1.empty()){
    cout<<q1.front()<<" ";
    q1.pop();
}

q1.empty();                 // 判断队列是否为空
q1.size();                  // 返回队列大小
q1.front();                 // 返回队头元素
q1.back();                  // 返回队尾元素
```

<br>

---

### 【-】priority_queue

优先队列 (堆)

```cpp
#include <queue>   // priority_queue 包含在 queue 中
```

#### 创建

```cpp
priority_queue<int> p1;     // 空优先队列，默认大顶堆
priority_queue<int, vector<int>, greater<int>> a;   // 小顶堆
```

#### 增加

```cpp
p1.push(6);                 // 入队
```

#### 删除

```cpp
p1.pop();                   // 出队
```

#### 修改

改不了一点。

#### 查找

```cpp
// 遍历优先队列 会清空优先队列
// 如果是大顶堆，遍历出来的是降序序列
while(!p1.empty()){ 
    cout<<p1.top()<<" ";
    p1.pop();
}

p1.empty();                 // 判断优先队列是否为空
p1.size();                  // 返回优先队列大小
p1.top();                   // 返回队头元素
```


<br>

---

## 关联式容器

所谓关联式容器，就是将数据元素组织成键值对的容器。

* 元素按照一定的排序规则组织的，而不是像顺序容器那样按照元素的插入顺序组织的。
* 关联容器的元素类型是pair类型，pair类型的第一个元素是键值，第二个元素是实值。

### 树

#### 二叉搜索树 BST

#### 平衡二叉树 AVLT

#### 平衡二叉搜索树 BBST

#### 红黑树 RBT


### 有序

map 和 set 底层实现是 **红黑树**，所以其元素是有序的。

| | map | set |
|:-:|:-:|:-:|
| **唯一** | map | set |
| **可重** | multimap | multiset |


### set

### multiset

### map

### multimap


### 无序

unordered_map 和 unordered_set 底层实现是 **哈希表**，所以其元素是无序的。

| | unordered_map | unordered_set |
|:-:|:-:|:-:|
| **唯一** | unordered_map | unordered_set |
| **可重** | unordered_multimap | unordered_multiset |


### unordered_set

### unordered_multiset

### unordered_map

### unordered_multimap


##

### set

集合

set 的元素是唯一的，不能重复。

set 的底层实现是红黑树，所以 set 的元素是有序的。

```cpp
#include <set>
```

#### 创建

```cpp
set<int> s1;                // 元素类型是 int
set<pair<string, int>> s2;  // 元素类型是 pair 类型
```

#### 增加

```cpp
s.insert(6);                // 插入元素 6
s2.insert({"hello", 6});    // 插入元素 {"hello", 6}
```

#### 删除

```cpp
s.clear();                      // 清空所有元素
s.erase(6);                     // 删除元素 6
s2.erase({"hello", 6});         // 删除元素 {"hello", 6}
s.erase(s.begin());             // 删除第一个元素
s.erase(s.begin(), s.end());    // 删除所有元素
```

#### 修改

改不了。

#### 查找

```cpp
s.find(6);                      // 查找元素 6 返回迭代器
s.count(6);                     // 查找元素 6 的个数
s.lower_bound(6);               // 查找第一个大于等于 6 的元素 返回迭代器
s.upper_bound(6);               // 查找第一个大于 6 的元素 返回迭代器

auto it = s.equal_range(6);     // 查找第一个大于等于 6 和 第一个大于 6 的元素 返回迭代器
cout<<(*it.first)<<" "<<(*it.second);

// 遍历
for(auto it = s.begin(); it != s.end(); it++) cout<<(*it)<<" ";
for(auto i: s) cout<<i<<" ";
```

### unordered_set

无序集合

unordered_set 的元素是唯一的，不能重复。

unordered_set 的底层实现是哈希表，所以 unordered_set 的元素是无序的。

```cpp
#include <unordered_set>
```

#### 创建

```cpp
unordered_set<int> s1;                // 元素类型是 int
unordered_set<pair<string, int>> s2;  // 元素类型是 pair 类型
```

#### 增加

```cpp
s.insert(6);                // 插入元素 6
s2.insert({"hello", 6});    // 插入元素 {"hello", 6}
```

#### 删除

```cpp
s.clear();                      // 清空所有元素
s.erase(6);                     // 删除元素 6
s2.erase({"hello", 6});         // 删除元素 {"hello", 6}
s.erase(s.begin());             // 删除第一个元素
s.erase(s.begin(), s.end());    // 删除所有元素
```

#### 修改

改不了。

#### 查找

```cpp
s.find(6);                      // 查找元素 6 返回迭代器
s.count(6);                     // 查找元素 6 的个数
```

### multiset

可重集合

multiset 的元素是可以重复的。

multiset 的底层实现是红黑树，所以 multiset 的元素是有序的。

```cpp
#include <set>
```

#### 创建

```cpp
multiset<int> s1;                // 元素类型是 int
multiset<pair<string, int>> s2;  // 元素类型是 pair 类型
```

#### 增加

```cpp
s.insert(6);                // 插入元素 6
s2.insert({"hello", 6});    // 插入元素 {"hello", 6}
```

#### 删除

```cpp
s.clear();                      // 清空所有元素
s.erase(6);                     // 删除元素 6
s2.erase({"hello", 6});         // 删除元素 {"hello", 6}
s.erase(s.begin());             // 删除第一个元素
s.erase(s.begin(), s.end());    // 删除所有元素
```

#### 修改

改不了。

#### 查找

```cpp
s.find(6);                      // 查找元素 6 返回迭代器
s.count(6);                     // 查找元素 6 的个数
s.lower_bound(6);               // 查找第一个大于等于 6 的元素 返回迭代器
s.upper_bound(6);               // 查找第一个大于 6 的元素 返回迭代器

s.equal_range(6);               // 查找第一个大于等于 6 和 第一个大于 6 的元素 返回迭代器
// 如果没有大于等于 6 的元素，那么第一个迭代器指向第一个大于 6 的元素，返回的两个迭代器相等
```

### unordered_multiset

```cpp
#include <unordered_set>
```

无序可重集合

unordered_multiset 的元素是可以重复的。

unordered_multiset 的底层实现是哈希表，所以 unordered_multiset 的元素是无序的。

#### 创建

```cpp
multiset<int> s1;                // 元素类型是 int
multiset<pair<string, int>> s2;  // 元素类型是 pair 类型
```

#### 增加

#### 删除

#### 修改

#### 查找

---
### map

映射

#### 创建

#### 增加

#### 删除

#### 修改

#### 查找

### unordered_map

无序映射

#### 创建

#### 增加

#### 删除

#### 修改

#### 查找

### multimap

可重映射

#### 创建

#### 增加

#### 删除

#### 修改

#### 查找

### unordered_multimap

无序可重映射

#### 创建

#### 增加

#### 删除

#### 修改

#### 查找