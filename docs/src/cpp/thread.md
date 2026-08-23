## 0 关于此文

对 C++ 的补充

* 以 [《C++ 并发编程实战》](https://nj.gitbooks.io/c/content/) 为主线

<br>

---

## 1 你好，C++的并发世界

### 并发与并行

1. 并发（Concurrency）是逻辑上的，并行（Parallelism）是物理上的

    * 并发是指一个 **时间段** 内有多个程序在同一个处理器上运行
    
    * 并行是指多个处理器或者是多核的处理器 **同一时刻** 运行多个程序

    > 当关注的重点在于任务分离或任务响应时，就会讨论到程序的并发性
    > 
    > 在讨论使用当前可用硬件来提高批量数据处理的速度时，我们会讨论程序的并行性

2. 并发包含并行

    * 并发是指在同一时刻有多个线程在同一个处理器上交替运行

    * 如果有多个处理器，那么这些线程可能会同时运行，此时并发包含了并行

    ```mermaid
    graph LR
    1[核心 1] --> A[task a] --> B[task b] --> C[task c]
    2[核心 2] --> D[task c] --> E[task b] --> F[task a]

    cpu[cpu] --> 1
    cpu[cpu] --> 2
    ```

3. 并发适用于 I/O 密集型任务，并行适用于 CPU 密集型任务

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
        std::thread t(f, 1e3);
        // 调用的函数是 f
        // 传递的参数是 1e3
        t.join();
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
        std::thread t(&A::f, &a, 1e3);
        // 调用的函数是 A::f
        // 调用的对象是 a
        // 传递的参数是 1e3
        t.join();
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
        std::thread t(p, 1e3);  // 创建线程 t
        // 调用的函数是 f
        // 传递的参数是 1e3
        t.join();
        return 0;
    }    
    ```

4. 函数对象

    ```cpp
    class A {
       public:
        A() = default;

        // 重载 () 运算符
        void operator()(int n) {
            for (int i = 1; i <= n; i++)
                std::cout << i << std::endl;
        }
    };

    int main() {
        std::thread t{A(), 1e3};
        // 调用的是 A 的临时对象
        // 传递的参数是 1e3
        t.join();
        return 0;
    }
    ```

5. `Lambda`

    ```cpp
    int main() {
        std::thread t(
            [](int n) {
                for (int i = 1; i <= n; i++)
                    std::cout << i << std::endl;
            },
            1e3);
        // 调用的函数是 lambda
        // 传递的参数是 1e3
        t.join();
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
        std::thread t(func, 1e3);  // 创建线程 t
        // 调用的函数是 func
        // 传递的参数是 1e3
        t.join();
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
        std::thread t(func);
        // 调用的函数是 func
        // 传递的参数是 1e3
        t.join();
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

### 管理线程 jthread

```cpp
int main() {
    std::jthread t([](std::stop_token st) {
        while (!st.stop_requested()) {  // 是否收到停止请求
            std::cout << "running\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << "stop\n";
    });

    std::this_thread::sleep_for(std::chrono::seconds(3));

    t.request_stop();  // 发送停止信号

    return 0;  // jthread 自动 join
}
```

<br>

---

## 3 线程间共享数据

### mutex 锁

* `std::mutex`

    ```cpp
    std::mutex mtx; // 创建一个互斥锁

    void f() {
        mtx.lock();   // 上锁
        // 临界区代码
        mtx.unlock(); // 解锁
    }
    ```

* `std::shared_mutex`

    ```cpp
    std::shared_mutex smtx; // 创建一个共享互斥锁

    void read() {
        smtx.lock_shared();   // 上共享锁
        // 读取共享数据
        smtx.unlock_shared(); // 解锁共享锁
    }
    ```

* `std::timed_mutex`

    ```cpp
    std::timed_mutex tmtx; // 创建一个定时互斥锁

    void f() {
        if (tmtx.try_lock_for(std::chrono::seconds(1))) { // 尝试上锁，最多等待 1 秒
            // 临界区代码
            tmtx.unlock(); // 解锁
        } else {
            // 上锁失败，处理超时情况
        }
    }
    ```

* `std::recursive_mutex`

    递归互斥锁，允许同一个线程多次上锁同一个互斥锁

* `std::recursive_timed_mutex`

### lock 锁管理器

* `std::lock_guard`

    ```cpp
    std::mutex mtx; // 创建一个互斥锁

    void f() {
        std::lock_guard<std::mutex> lock(mtx); // 上锁
        // 临界区代码
    } // 离开作用域时自动解锁
    ```

* `std::shared_lock`

    ```cpp
    std::shared_mutex smtx; // 创建一个共享互斥锁

    void read() {
        std::shared_lock<std::shared_mutex> lock(smtx); // 上共享锁
        // 读取共享数据
    } // 离开作用域时自动解锁共享锁

    void write() {
        std::unique_lock<std::shared_mutex> lock(smtx); // 上独占锁
        // 写入共享数据
    } // 离开作用域时自动解锁独占锁
    ```

* `std::unique_lock`

    ```cpp
    std::mutex mtx; // 创建一个互斥锁

    void f() {
        std::unique_lock<std::mutex> lock(mtx); // 上锁
        // 临界区代码
        lock.unlock(); // 手动解锁
        // 其他代码
        lock.lock();   // 再次上锁
        // 临界区代码
    } // 离开作用域时自动解锁
    ```

* `std::scoped_lock`

    ```cpp
    std::mutex mtx1, mtx2; // 创建两个互斥锁

    void f() {
        std::scoped_lock lock(mtx1, mtx2); // 同时上锁两个互斥锁
        // 临界区代码
    } // 离开作用域时自动解锁两个互斥锁
    ```

## 4 同步并发操作

### candition_variable 条件变量


### promise / future 异步操作


<br>

---

## 5 原子类型操作

### atomic 原子操作

> 为什么更快
>
> 1. 现代 CPU 通常通过[缓存一致性协议](https://www.amazonaws.cn/what-is/cache-consistency/)独占缓存行实现原子性，并不是每次都锁总线
>
> 2. 原子操作主要的优势是省掉了阻塞、唤醒和上下文切换的开销
>
> 3. 原子操作只适用于简单的操作，如计数器、标志位等
>
> * 在高竞争的情况下，原子操作可能会导致自旋等待，从而降低性能

* `std::atomic<bool>`

    ```cpp
    std::atomic<bool> flag(false);
    flag.store(true)    // 原子存储
    flag.load()         // 原子加载
    ```

* `std::atomic<int>`

    ```cpp
    std::atomic<int> counter(0);
    counter.fetch_add(1) // 原子加 1
    counter.fetch_sub(1) // 原子减 1
    ```

### memory_order 内存序

* `std::memory_order_relaxed`
    
    不建立与其他内存操作之间的顺序关系，适用于计数器等简单操作

* `std::memory_order_acquire` for `load`
    
    保证当前线程中，所有在 acquire 之后的读操作，不会被重排到 acquire 之前

* `std::memory_order_release` for `store`

    保证当前线程中，所有在 release 之前的写操作，不会被重排到 release 之后

* `std::memory_order_acq_rel`

* `std::memory_order_seq_cst` for `load` and `store`

    保证全局顺序性，所有线程都看到相同的顺序，是最严格的内存序，默认使用此内存序

### CAS

<br>

---

## 6 有锁并发数据结构设计

### MPMC

```cpp
template <typename QAQ>
class MPMCQueue {
   public:
    bool push(QAQ value) {
        {
            std::lock_guard<std::mutex> lock(_mutex);
            if (_closed)
                return false;
            _queue.push(std::move(value));
        }

        _cv.notify_one();
        return true;
    }

    bool pop(QAQ& value) {
        std::unique_lock<std::mutex> lock(_mutex);

        _cv.wait(lock, [this] { return !_queue.empty() || _closed; });

        if (_queue.empty() && _closed)
            return false;

        value = std::move(_queue.front());
        _queue.pop();
        return true;
    }

    void close() {
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _closed = true;
        }
        _cv.notify_all();
    }

   private:
    std::queue<QAQ> _queue;
    std::mutex _mutex;
    std::condition_variable _cv;
    bool _closed = false;
};
```

<br>

---


## 7 无锁并发数据结构设计

### SPSC

```cpp
template <typename QAQ, std::size_t SIZE>
class SPSCQueue {
   public:
    bool push(const QAQ& value) {
        auto tail = _tail.load(std::memory_order_relaxed);

        if (tail - _head.load(std::memory_order_acquire) >= SIZE)
            return false;  // full
        _queue[tail % SIZE] = value;

        _tail.store(tail + 1, std::memory_order_release);
        return true;
    }

    bool pop(QAQ& value) {
        auto head = _head.load(std::memory_order_relaxed);

        if (head == _tail.load(std::memory_order_acquire))
            return false;  // empty
        value = _queue[head % SIZE];

        _head.store(head + 1, std::memory_order_release);
        return true;
    }

   private:
    std::array<QAQ, SIZE> _queue;
    alignas(64) std::atomic<std::size_t> _head{0};  // 内存对齐以独享 cache line
    alignas(64) std::atomic<std::size_t> _tail{0};
};
```

<br>

---


## 8 并发代码设计



<br>

---


## 9 高级线程管理

### Thread Pool

```cpp
class ThreadPool {
   public:
    explicit ThreadPool(size_t threadNum) {
        while (threadNum--)  // 创建线程
            _workers.emplace_back([this] {
                std::function<void()> task;
                while (_tasks.pop(task))  // 取不到任务会阻塞在 pop
                    task();
            });
    }

    bool submit(std::function<void()> task) { return _tasks.push(std::move(task)); }

    ~ThreadPool() {
        _tasks.close();                // 不再接收新任务
        for (auto& worker : _workers)  // 等待所有线程退出
            if (worker.joinable())
                worker.join();
    }

   private:
    MPMCQueue<std::function<void()>> _tasks;
    std::vector<std::thread> _workers;
};
```

<br>

---


## 10 多线程程序的测试和调试


