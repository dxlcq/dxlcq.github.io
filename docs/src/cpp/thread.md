## 0 关于此文

对 C++ 的补充

* 以 [《C++ 并发编程实战》](https://www.kdocs.cn/l/ce26I9gpXyOu) 为主线

<br>

---

## 1 你好，C++的并发世界

### 并发与并行

1. 并发（Concurrency）是逻辑上的，并行（Parallelism）是物理上的。

    * 并发是指一个 **时间段** 内有多个程序在同一个处理器上运行
    
    * 并行是指多个处理器或者是多核的处理器 **同一时刻** 运行多个程序

    > 当关注的重点在于任务分离或任务响应时，就会讨论到程序的并发性
    > 在讨论使用当前可用硬件来提高批量数据处理的速度时，我们会讨论程序的并行性

2. 并发包含并行

    * 并发是指在同一时刻有多个线程在同一个处理器上交替运行

    * 如果有多个处理器，那么这些线程可能会同时运行，此时并发包含了并行

3. 并发适用于 I/O 密集型任务，并行适用于 CPU 密集型任务

<br>

---

### 为什么使用并发

1. 为了分离关注点

    * 通过并发，可以将程序分解为多个独立的任务，每个任务都可以独立地执行

2. 为了性能

<br>

---

## 2 线程管理


### 启动线程 thread

`std::thread` 接受多种可调用对象

1. 普通函数

```cpp
void f(int n) {
  for (int i = 1; i <= n; i++)
    std::cout << i << std::endl;
}

int main() {
  std::thread t1(f, 1e3);   // 创建线程 t1
  // 调用的函数是 f
  // 传递的参数是 1e3
  t1.join();
  return 0;
}
```

2. 成员函数

```cpp
class A {
public:
  void f(int n) {
    for (int i = 1; i <= n; i++)
      std::cout << i << std::endl;
  }
};

int main() {
  A a;
  std::thread t1(&A::f, &a, 1e3);  // 创建线程 t1
  // 调用的函数是 A::f
  // 调用的对象是 a
  // 传递的参数是 1e3
  t1.join();
  return 0;
}
```

3. 函数指针

```cpp
void f(int n) {
  for (int i = 1; i <= n; i++)
    std::cout << i << std::endl;
}

int main() {
  void (*p)(int) = f;
  std::thread t1(p, 1e3);   // 创建线程 t1
  // 调用的函数是 f
  // 传递的参数是 1e3
  t1.join();
  return 0;
}
```

4. 函数对象

```cpp
#include <iostream>
#include <thread>

class A {
public:
  void operator()(int n) {
    for (int i = 1; i <= n; i++)
      std::cout << i << std::endl;
  }
};

int main() {
  A a;
  std::thread t1(a, 1e3);   // 创建线程 t1
  // 调用的函数是 f
  // 传递的参数是 1e3
  std::thread t2{A(), 1e3};
  // 调用的是 A 的临时对象
  // 传递的参数是 1e3
  t1.join();
  t2.join();
  return 0;
}
```

5. `Lambda`

```cpp
int main() {
  std::thread t1(
      [](int n) {
        for (int i = 1; i <= n; i++)
          std::cout << i << std::endl;
      },
      1e3); // 创建线程 t1
  // 调用的函数是 lambda
  // 传递的参数是 1e3
  t1.join();
  return 0;
}
```

6. `std::function`

```cpp
void f(int n) {
  for (int i = 1; i <= n; i++)
    std::cout << i << std::endl;
}

int main() {
  std::function<void(int)> func = f;
  std::thread t1(func, 1e3); // 创建线程 t1
  // 调用的函数是 func
  // 传递的参数是 1e3
  t1.join();
  return 0;
}
```

7. `std::bind`

```cpp
void f(int n) {
  for (int i = 1; i <= n; i++)
    std::cout << i << std::endl;
}

int main() {
  auto func = std::bind(f, 1e3);
  std::thread t1(func); // 创建线程 t1
  // 调用的函数是 func
  // 传递的参数是 1e3
  t1.join();
  return 0;
}
```

<br>

---

### 分离线程 detach


<br>

---

### 等待线程 join


<br>

---


## thread

## thread：线程

* `join` 方式：等待线程结束，再继续执行。
* `detach` 方式：分离线程，线程结束后自动回收资源。

```cpp  
#include <iostream>
#include <thread>
using namespace std;

void func(int i){
    cout << "hello "<< i <<" Thread" << endl;
}

int main(){
    thread (func, 1).detach();  // 创建匿名线程并分离
                                // 主线程结束，此线程也会结束
    thread t(func, 2);  // 创建线程 t
    t.join();           // 等待线程 t 结束
    return 0;
}
```
主函数创建了一个线程，然后分离，主函数结束，线程也结束。
主函数创建了一个线程，然后等待，主函数结束，线程也结束。

## this_thread：线程本身

---

## mutex

## mutex：互斥量

* `lock`：上锁。
* `unlock`：解锁。

```cpp
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int value;  // 分别对此变量进行加 [1,1e6] 和减 [1,1e6] 操作
int m_value;// 互斥锁保护的变量，同样进行加减操作
mutex mtx;  // 互斥锁

void add(){
    for(int i = 1; i <= 1e6; i++) value++;
}

void sub(){
    for(int i = 1; i <= 1e6; i++) value--;
}

void m_add(){
    for(int i = 1; i <= 1e6; i++){
        mtx.lock();   // 上锁
        m_value++;
        mtx.unlock(); // 解锁
    }
}

void m_sub(){
    for(int i = 1; i <= 1e6; i++){
        mtx.lock();   // 上锁
        m_value--;
        mtx.unlock(); // 解锁
    }
}

int main(){
    thread t1 (add);
    thread t2 (sub);
    t1.join();
    t2.join();
    cout<<value<<endl;

    thread t3 (m_add);
    thread t4 (m_sub);
    t3.join();
    t4.join();
    cout<<m_value<<endl;
    return 0;
}
```

主函数首先创建了两个线程，分别对 value 进行加减操作，然后输出 value 的值。
在加减操作中，没有对 value 进行保护，所以最后输出的 value 的值不一定是 0。

主函数接着创建了两个线程，分别对 m_value 进行加减操作，然后输出 m_value 的值。
在加减操作中，对 m_value 进行了保护，所以最后输出的 m_value 的值一定是 0。

## lock_guard：锁保护

简单理解，作用域内自动上锁解锁。

```cpp
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx;  // 锁
int value = 0;

void add(int i){
    for(int i=1; i<=1e6; i++){
        lock_guard<mutex> lock(mtx);  // 加锁
        value++;
    }
}

void sub(int i){
    for(int i=1; i<=1e6; i++){
        lock_guard<mutex> lock(mtx);  // 加锁
        value--;
    }
}

int main(){
    thread t1(add, 1);
    thread t2(sub, 2);
    t1.join();
    t2.join();
    cout << value << endl;
    return 0;
}
```

主函数创建了两个线程，分别对 value 进行加减操作，然后输出 value 的值。
在加减操作中，使用 lock_guard<mutex> lock(mtx) 对 value 进行保护，所以最后输出的 value 的值一定是 0。

## unique_lock：独占锁

相较于 lock_guard，unique_lock 更加灵活，提供了更多的功能。

**延迟锁定**

在构建 unique_lock 对象时，可以指定参数 `std::defer_lock`，表示延迟锁定，即不上锁。
在后面需要上锁时，调用 `lock` 方法即可。

```cpp
#include <mutex>

std::mutex mtx; // 一个互斥锁

void f(){
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock); // 延迟锁定
    // 执行一些不需要互斥访问的操作
    lock.lock();    // 在需要时手动上锁
    // 执行需要互斥访问的操作
}   // 在作用域结束时自动解锁

int main() {
    f();
    return 0;
}
```

**递归锁定**

`std::unique_lock` 允许同一个线程多次上锁同一个互斥锁，即递归锁定。在这种情况下，线程需要在解锁时正确地进行相应次数的解锁操作，否则互斥锁不会被解锁。

```cpp
#include <iostream>
#include <mutex>

std::recursive_mutex mtx; // 一个递归互斥锁

void recursiveFunction(int depth) {
    std::unique_lock<std::recursive_mutex> lock(mtx, std::defer_lock);
    if (depth > 0) {
        lock.lock(); // 手动上锁
        std::cout << "Depth: " << depth << std::endl;
        recursiveFunction(depth - 1); // 递归调用
    }
}

int main() {
    recursiveFunction(3);
    return 0;
}
```


---

## atomic

原子操作是一种不可被中断的操作，要么全部执行，要么完全不执行，不会出现在操作过程中被其他线程干扰的情况。在并发编程中，原子操作是确保数据一致性和避免竞态条件的关键。

## atomic：原子操作

包装基本数据类型，提供原子性的读取、修改、操作。

**加减、与非、异或**

```cpp
#include <atomic>
#include <iostream>

std::atomic<int> counter(-2); // 创建一个原子整数

void increment() {
    counter.fetch_add(1, std::memory_order_relaxed); // 原子性地增加计数器的值
}

int main() {
    increment();
    std::cout << counter.load(std::memory_order_acquire) << std::endl;
    return 0;
}
```

**原子加载和存储**

```cpp
#include <atomic>
#include <iostream>

std::atomic<int> value(42);

int readValue() {
    return value.load(std::memory_order_acquire); // 原子加载操作
}

void modifyValue(int newValue) {
    value.store(newValue, std::memory_order_release); // 原子存储操作
}

int main() {
    modifyValue(43);
    std::cout << readValue() << std::endl;
    return 0;
}
```

**比较交换**

* 同步原语
* 无锁数据结构
* 解决竞态条件
* 乐观锁

## atomic_flag：轻量级原子操作


---

## condition_variable

条件变量，允许线程等待某个特定条件得到满足，然后再继续执行。
它提供了一个阻塞机制，当某个条件不满足时，线程可以等待在条件变量上，直到其他线程通知它满足条件。

## condition_variable：条件变量

## condition_variable_any：通用条件变量

---

## future

## future：异步操作

## shared_future：共享异步操作

## promise：异步操作

## packaged_task：异步操作



---

[康康](https://www.zhihu.com/question/397916107)

## 线程池

1. 线程管理者

初始化、创建线程，启动、停止线程，调配任务。

2. 工作线程

执行任务。

3. 任务队列

存放任务。一种缓冲机制，平衡生产者和消费者的速度差异。


