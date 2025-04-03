## 参考

* [hmbdc](https://github.com/hmbdc-dev/hmbdc)

<br>

---

## 安装

```bash
apt install g++-12
make -j8 CXX=g++-12
```

在 docker 中运行时，需要 `--ipc=host` 参数。

## 一些概念

* `TIPS` C++ Type Inferred Pub/Sub，类型推断发布订阅，消息以 C++ 类型 struct/class 定义

* `POTS` Pub/sub On Topic String，基于主题字符串的发布订阅

* `Node` 每个 Node 代表一个 OS 线程，其实就是 sender / receiver

* `Domain` 多个 Node 组成一个 Domain，消息通过 Domain 传播（发布/订阅）

* fa运行逻辑:

    1. 

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

// 列出所有主题，在所有 .h / .cpp 文件中，顺序应当一致
char const* AllTopics[] = {
    "/hello",
    "/hi-back",
};

/// write a Node to publish on the topic "/hello" @1HZ for 10 times and print out the echoing "/hi-back"
struct Sender : pots::Node<Sender> {
    Sender() 
    : Node{
        {"/hi-back"}        // subscribe topics
        , {"/hello"}        // publish topics
    } {
        // schedule the 1HZ timer - first firing asap from now
        Node::schedule(time::SysTime::now(), timer1Hz);
    }

    /// node/thread name
    char const* hmbdcName() const {return "Sender";}

    /// called only once before any message dispatching (or timer callback) happens
    virtual void messageDispatchingStartedCb(std::atomic<size_t> const*) override {
        std::cout << "start messaging and timers" << std::endl;
    }

    // callback called once whenever this Sender
    // thread is unblocked - by new message arriving, timer wake up
    // or max blocking timeouts (1 sec by default)
    void invokedCb(size_t count) override {
        if (count) std::cout << "msgs just received =" << count << std::endl;
    }

    /// message callback
    virtual void potsCb(std::string_view topic, void const* msg, size_t msgLen) override {
        std::cout << static_cast<char const*>(msg) << std::endl;
    }

    /// timer
    time::ReoccuringTimer timer1Hz{time::Duration::seconds(1) // re-occure every 1 sec
        , [this](auto&&, auto&&) {                            // do this when timer fires  
        static auto count = 10;
        if (count--) { 
            std::cout << "sending a Hello" << std::endl;
            auto msg = "hello world!";
            publish("/hello", msg, strlen(msg) + 1);
        } else {
            throw (ExitCode(0)); // node finished and exits it by throw an exception
        }
    }};
};

/// write a Node subscribe to the topic "/hellow" and echo back on "/hi-back"
struct Receiver : pots::Node<Receiver> {
    Receiver()
    : Node(
        {"/hello"}          // 1 subscription
        , {"/hi-back"})     // publish 1 topic
    {}
    char const* hmbdcName() const {return "Receiver";}
    /// message callback - won't compile if missing
    void potsCb(std::string_view topic, void const* msg, size_t msgLen) {
        std::cout << static_cast<char const*>(msg) << std::endl;

        std::string back{"world hi back"};
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
        domain.add(sender);                     /// start sender as a thread
        domain.startPumping();                  /// start process-level message IO
        sleep(10);           // let the sender thread run for a while
        domain.stop();       // wrap up and exit
        domain.join();
    } else {
        cout << "running as receiver, ctrl-c to exit" << endl;
        Receiver recv;
        domain.add(recv).startPumping();            /// recv Node and IO started
        /// handle ctrl-c
        hmbdc::os::HandleSignals::onTermIntDo([&](){domain.stop();});
        domain.join();
    }
}
```