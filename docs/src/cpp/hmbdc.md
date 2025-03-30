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

* `Node` 每个 Node 代表一个 OS 线程，可以发布/订阅消息

* `Domain` 多个 Node 组成一个 Domain，消息通过 Domain 传播（发布/订阅）

## example 解析

### hello_world.cpp

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

// 搞一个消息类型试一试
struct Hello : hasTag<1001> { // 为每个消息类型分配一个16位的标签，标签需要大于1000且唯一
    char msg[6] = "hello";
};

/// write a simple Node subscribe to the above message
struct Receiver : Node<Receiver
    , std::tuple<Hello> // only subscribe Hello
    , std::tuple<>      // not publishing anything
> {
    /// message callback - won't compile if missing
    void handleMessageCb(Hello const& m) {
        cout << m.msg << endl;
    }
};

int main(int argc, char** argv) {
    using namespace std;
    if (argc < 2) {
        cerr << argv[0] << " local-ip [recv]" << endl;
        cerr << "start application as sender (default) or as Receiver" << endl;
        return -1;
    }
    std::string ifaceAddr = argv[1];
    bool isSender = argc <= 2;

    Config config; //other config values are default
    config.put("ifaceAddr", ifaceAddr);//which net IP to use for net communication
    
    SingletonGuardian<tcpcast::Protocol> g; //RAII for tcpcast::Protocol resources

    if (isSender) {
        cout << "running as sender, ctrl-c to exit" << endl;
        using MyDomain = Domain<std::tuple<>    /// no subscribing
            , ipc_property<>                    /// default IPC params (using shared mem)
            , net_property<tcpcast::Protocol>>; /// use tcpcast as network transport
        auto domain = MyDomain{config};
        domain.startPumping();
        /// handle ctrl-c
        auto stopped = std::atomic<bool>{false};
        hmbdc::os::HandleSignals::onTermIntDo([&](){stopped = true;});
        while (!stopped) { // until ctrl-c pressed
            // publish is a fast/async and theadsafe call, all subscribing Nodes in the domain receive it
            domain.publish(Hello{});
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        domain.stop();
        domain.join();
    } else {
        cout << "running as receiver, ctrl-c to exit" << endl;
        using MyDomain = Domain<std::tuple<Hello>   /// subscribe to Hello - compile time checked
            , ipc_property<>                        /// match sender side
            , net_property<tcpcast::Protocol>>;     /// match sender side
        auto domain = MyDomain{config};
        Receiver recv;
        domain.add(recv).startPumping();            /// recv Node and IO started
        /// handle ctrl-c
        hmbdc::os::HandleSignals::onTermIntDo([&](){domain.stop();});
        domain.join();
    }
}
```

