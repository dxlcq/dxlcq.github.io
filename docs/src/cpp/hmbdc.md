## 参考

* [hmbdc](https://github.com/hmbdc-dev/hmbdc)

<br>

---

## 编译

全量编译

```bash
apt install g++-12 libboost-all-dev
make -j8 CXX=g++-12
```

单独编译

```
g++-12 hello-world.cpp -O3 -g -std=c++20 -pthread -D BOOST_BIND_GLOBAL_PLACEHOLDERS -I/root/dxl/hmbdc-master/ -lrt
```

> * `-std=c++20` 低于 c++20 无法通过编译
> * `-D BOOST_BIND_GLOBAL_PLACEHOLDERS` 在编译开始前定义了一个宏

在 docker 中运行时，需要 `--ipc=host` 参数

<br>

---

## 一些概念

* `TIPS` C++ Type Inferred Pub/Sub，类型推断发布订阅，消息以 C++ 类型 struct/class 定义

* `POTS` Pub/sub On Topic String，基于主题字符串的发布订阅

* `Node` 每个 Node 代表一个 OS 线程，其实就是 sender / receiver

* `Domain` 多个 Node 组成一个 Domain，消息通过 Domain 传播（发布/订阅）

<br>

---

## 运行逻辑

* 发送端和接收端实际上都可以接发消息，区别在于：

    * Sender 的实现通常包括一个定时器或者主动触发事件的机制。它的重点是 **定期发送消息**，不需要等待接收到其他消息

    * Receiver 则依赖于 **消息的到达**，它的核心是 **订阅和响应消息**，通常包含一个处理回调（例如 `potsCb`）来处理接收到的消息。

### TIPS

**发送端**

1. 通过单例模式创建 HMBDC 网络栈的上下文

    ```cpp
    hmbdc::app::SingletonGuardian<hmbdc::tips::tcpcast::Protocol> g;
    ```

2. 通过配置文件启动 domain（需要指定两部分配置）

    ```cpp
    Config config;

    auto domain = Domain<std::tuple<>
        , ipc_property<>
        , net_property<tcpcast::Protocol>>{config};
    
    domain.startPumping();
    ```

3. 发布消息：向 domain 中 push 消息结构体

    ```cpp
    struct Hello : hasTag<1001> { 
        char msg[6] = "hello";
    };

    domain.publish(Hello{});
    ```

**接收端**

1. 通过单例模式创建 HMBDC 网络栈的上下文

2. 创建消息结构体

    ```cpp
    struct Hello : hasTag<1001> { 
        char msg[6] = "hello";
    };
    ```

3. 创建 domain（还未启动）

    ```cpp
    Config config

    auto domain = Domain<std::tuple<Hello>
        , ipc_property<>
        , net_property<tcpcast::Protocol>>{config};
    ```

4. 创建 Receiver Node

    ```cpp
    struct Receiver : Node<Receiver
        , std::tuple<Hello>>
        , std::tuple<>> {

        void handleMessageCb(Hello const& m) {
            cout << m.msg << endl;
        }
    };
    ```

5. 向 domain 注册 Receiver Node 并启动

    ```cpp
    domain.add(recv).startPumping();
    ```

### POTS 

**发送端**

1. 列出所有的 topic

    ```cpp
    char const* AllTopics[] = {
        "/hello",
        "/hi-back",
    };
    ```

2. 通过单例模式创建 HMBDC 网络栈的上下文

    ```cpp
    hmbdc::pattern::SingletonGuardian<pots::MessageConfigurator> g{AllTopics};
    ```

3. 创建 Domain

    ```cpp
    auto domain = pots::DefaultDomain{ifaceAddr};
    ```

4. 创建 Sender Node

5. 向 domain 注册 Sender Node 并启动

    ```cpp
    domain.add(sender);
    domain.startPumping();
    ```

**接收端**

1. 列出所有的 topic

2. 通过单例模式创建 HMBDC 网络栈的上下文

3. 创建 Domain

4. 创建 Receiver Node

5. 向 domain 注册 Receiver Node 并启动


<br>

---

## example 解析

### hello-world.cpp

```cpp
// hello-world for hmbdc TIPS
// - domain 和 Node 的概念见 https://github.com/hmbdc-dev/hmbdc
// 构建：
// g++ hello-world.cpp -O3 -std=c++1z -pthread -D BOOST_BIND_GLOBAL_PLACEHOLDERS -I/usr/include/boost -lrt -o /tmp/hw
// 我试了，编不了，还是得去 hmbdc 使用 make，记得加 -g
//
// 下面是一个示例，有 term1 和 term2 两个终端，分别作为 receiver 和 sender，先启动接收端，再启动发送端
// [term1] ./hello-world 127.0.0.1 recv
// running as receiver, ctrl-c to exit
//
// [term2] ./hello-world 127.0.0.1
// running as sender, ctrl-c to exit
//
// PS: 可以启动多个send，recv都可以收到
//
// to debug:
// 必要时需要清理共享内存 "rm /dev/shm/*" 
// - SHM 的所有权由 ipcTransportOwnership 配置项决定，该项的具体配置可以在 tips/DefaultUserConfig.hpp 文件中找到
#include "hmbdc/tips/tcpcast/Protocol.hpp"  // 引入 tcpcast 传输协议，用于不同主机之间（inter-host）基于 TCP 的通信
#include "hmbdc/tips/Tips.hpp"              // hmbdc(TIPS)的核心头文件，定义了跨线程、进程和网络的发布/订阅通信机制
#include "hmbdc/os/Signals.hpp"             // 处理 UNIX 信号（SIGTERM、SIGINT），确保当进程收到这些信号时，能够优雅退出

#include <iostream>

using namespace std;
using namespace hmbdc::app;
using namespace hmbdc::tips;

// 搞一个消息类型试一试，消息类型为 Hello
struct Hello : hasTag<1001> { // 为每个消息类型分配一个16位的标签，标签需要大于1000且唯一
    char msg[6] = "hello";
};

// 编写一个简单的 Node 订阅上述消息
struct Receiver : Node<Receiver // 标识当前 Node 的类型为 Receiver，用于接收消息
    , std::tuple<Hello>         // 订阅 Hello 消息，如果需要订阅多个：std::tuple<Hello, World, ...>
    , std::tuple<>              // 发布消息
> {
    // 消息回调，对于订阅的每个消息类型，都必须实现一个 handleMessageCb 函数，否则无法通过编译
    void handleMessageCb(Hello const& m) {
        cout << m.msg << endl;
    }
};

int main(int argc, char** argv) {
    using namespace std;
    // 判断传入参数数量
    if (argc < 2) {
        cerr << argv[0] << " local-ip [recv]" << endl;
        cerr << "start application as sender (default) or as Receiver" << endl;
        return -1;
    }
    // 拿到 IP
    std::string ifaceAddr = argv[1];
    bool isSender = argc <= 2;

    Config config;
    config.put("ifaceAddr", ifaceAddr); // 用于网络通信的 IP，仅修改一个配置项，其他保持默认

    // tcpcast::Protocol 是 HMBDC 网络栈的上下文
    // 通过 SingletonGuardian 单例确保只有一个上下文存在
    SingletonGuardian<tcpcast::Protocol> g; // RAII

    if (isSender) {
        cout << "running as sender, ctrl-c to exit" << endl;
        // 定义一个域
        using MyDomain = Domain<std::tuple<>    // 无需订阅（因为这是发送者）
            , ipc_property<>                    // 默认 IPC 参数（使用共享内存）
            , net_property<tcpcast::Protocol>>; // 使用 tcpcast 作为网络传输
        // 通过配置启动域
        auto domain = MyDomain{config};
        domain.startPumping();
        // 捕获 control+c，并通过原子变量 stopped 通知程序停止运行
        auto stopped = std::atomic<bool>{false};
        hmbdc::os::HandleSignals::onTermIntDo([&](){stopped = true;});
        // 直到 control+c 被按下 
        while (!stopped) {
            // 向 domain 中发布一个 Hello 消息，每秒一次
            domain.publish(Hello{});
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        domain.stop();
        domain.join();
    } else {
        cout << "running as receiver, ctrl-c to exit" << endl;
        using MyDomain = Domain<std::tuple<Hello>
            , ipc_property<>
            , net_property<tcpcast::Protocol>>;
        auto domain = MyDomain{config};
        Receiver recv;
        domain.add(recv).startPumping();    // 添加接收者并启动消息循环
        // 捕获 control+c，并通过原子变量 stopped 通知程序停止运行
        hmbdc::os::HandleSignals::onTermIntDo([&](){domain.stop();});
        domain.join();
    }
}
```

### hello-pots.cpp

```cpp
// hello world for hmbdc POTS 
// 同上
#include "hmbdc/pots/Pots.hpp"
#include "hmbdc/os/Signals.hpp"

#include <iostream>
#include <iterator>

using namespace hmbdc;

// 列出所有主题，在所有 .h 或 .cpp 文件中，顺序应当一致
char const* AllTopics[] = {
    "/hello",
    "/hi-back",
};

// 向 /hello 话题发布消息，并且每次收到 /hi-back 话题的消息时，输出接收到的消息内容
struct Sender : pots::Node<Sender> {
    Sender() 
    : Node{
        {"/hi-back"}        // 订阅 topics
        , {"/hello"}        // 发布 topics
    } {
        // 启动一个定时器，每秒触发一次，并且第一次触发尽可能快地发生
        Node::schedule(time::SysTime::now(), timer1Hz);
    }

    // 节点名称
    char const* hmbdcName() const {return "Sender";}

    // 节点的初始化阶段，所有消息的调度和定时器触发之前，框架会调用这个回调函数
    virtual void messageDispatchingStartedCb(std::atomic<size_t> const*) override {
        // 消息调度和定时器触发已经开始
        std::cout << "start messaging and timers" << std::endl;
    }

    // 每当此 Sender 线程被解锁时，回调函数会被调用一次。
    // 线程解锁的原因可能是：新消息到达、定时器唤醒，或者最大阻塞超时（默认 1 秒）。
    void invokedCb(size_t count) override {
        if (count) std::cout << "msgs just received =" << count << std::endl;
    }

    // 处理接收到的消息 - 消息回调，sender 可以不实现这个函数
    // topic: 消息所属主题
    // msg: 指向消息内容的指针
    // msgLen: 消息长度（字节数）
    virtual void potsCb(std::string_view topic, void const* msg, size_t msgLen) override {
        std::cout << static_cast<char const*>(msg) << std::endl;
    }

    /// timer
    time::ReoccuringTimer timer1Hz{time::Duration::seconds(1) // 每秒触发一次
        , [this](auto&&, auto&&) {                            // 在 timer 触发时执行此操作
        static auto count = 10;
        if (count--) { 
            std::cout << "sending a Hello" << std::endl;
            auto msg = "hello world!";
            publish("/hello", msg, strlen(msg) + 1);          // 向 "/hello" 发布消息
        } else {
            throw (ExitCode(0));    // 发送完成后，节点会抛出一个 ExitCode(0) 异常，表示它的任务已完成并退出。
        }
    }};
};

struct Receiver : pots::Node<Receiver> {
    Receiver()
    : Node(
        {"/hello"}          // 订阅 "/hello" topic
        , {"/hi-back"})     // 发布 "/hi-back" topic
    {}
    char const* hmbdcName() const {return "Receiver";}
    
    // 处理接收到的消息 回调函数 必须有，否则编译不过
    void potsCb(std::string_view topic, void const* msg, size_t msgLen) {
        std::cout << static_cast<char const*>(msg) << std::endl;

        std::string back{"world hi back"};
        // 发布消息到 "/hi-back"
        publish("/hi-back", back.c_str(), back.size() + 1);
    }
};

int main(int argc, char** argv) {
    using namespace std;
    if (argc < 2) {
        cerr << argv[0] << " local-ip [recv]" << endl;
        cerr << "start application as sender (default) or as Receiver" << endl;
        return -1;
    }
    auto ifaceAddr = argv[1];
    bool isSender = argc <= 2;
    
    // RAII
    // pots::MessageConfigurator 是 HMBDC pots 的上下文
    // 在程序运行早期，将 AllTopics 注册到 pots 的上下文中，使用单例模式实例化
    hmbdc::pattern::SingletonGuardian<pots::MessageConfigurator> g{AllTopics};
    // 使用的域
    auto domain = pots::DefaultDomain{ifaceAddr};

    if (isSender) {
        cout << "running as sender for 10 sec and exit" << endl;
        Sender sender;
        domain.add(sender);                     // 将 sender 添加到域中，作为线程启动
        domain.startPumping();                  // 启动进程级别的消息IO
        sleep(10);           // 让 sender 线程运行一段时间
        domain.stop();       // 完成并退出
        domain.join();       // 等待 sender 线程结束
    } else {
        cout << "running as receiver, ctrl-c to exit" << endl;
        Receiver recv;
        domain.add(recv).startPumping();
        // 捕获 control+c，并通过原子变量 stopped 通知程序停止运行
        hmbdc::os::HandleSignals::onTermIntDo([&](){domain.stop();});
        domain.join();
    }
}
```