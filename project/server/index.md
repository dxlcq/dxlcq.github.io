---
html:
    toc: true           # 打开侧边目录
    toc_depth: 6        # 打开的目录层级
    toc_float: true     # 侧边悬停
    collapsed: true     # 只显示高级别标题(2)
    smooth_scroll: true # 页面滚动,标题变化
    number_sections: false  # 显示标题编号
    theme: united
--- 

# README

一个



# Socket 套接字

* TCP/IP 分层模型

|       |       |
| :---: | :--- | 
| 应用层 | `HTTP` `FTP` `TELNET` ...| 
| 传输层 | `TCP` `UDP` `SCTP` ...|    
| 网络层 | `ARP` `IPV4` `ICMP` ... | 
| 物理层 | `WLAN` `LAN` ...|

*  Socket 工作流

|       |  |  服务器端  |       |       |  |  客户端  |                  
| :---: |  :---:  | :---: | --- | :---: |  :---:  | :---: |
| 1 | `socket()`| 创建 socket                   |  | 1 | `socket()`| 创建 socket|
| 2 | `bind()`  | 绑定 ip + port 至该 socket 上 |  | 2 | `connect()`| 连接指定 ip + port |
| 3 | `listen()`| 监听该 端口                   |  |   | 
| 4 | `accept()`| 接受来自服务端的连接请求        | | 3 | `send()` | 发送消息
| 5 | `read()`  | 从 socket 中读取字符          |  |  |  
| 6 | `close()` | 关闭 socket                   |  | 4 | `close()` | 关闭 socket

> Socket 通信过程:
> 1. 服务器端: 创建 socket
> 2. 服务器端: 绑定 ip + port
> 3. 服务器端: 监听 网络状态
> 4. `客 户 端`: 创建 socket
> 5. `客 户 端`: 连接 服务器端
> 6. 服务器端: 接受 `客户端`连接
> 7. `客 户 端`: 发送 消息
> 8. 服务器端: 读取 消息
> 9. `客 户 端`: 关闭 连接
> 10. 服务器端: 关闭 连接

> 其中, TCP的三次握手过程:
> 1. `客户端` 请求连接, `connect()阻塞` 
> 2. 服务器端收到请求, `accept()阻塞`, 向客户端发送连接确认信息, 等待`客户端`返回确认信息
> 3. `客户端` 发送连接确认信息, `connect()返回`, 服务器端收到确认信息, `accept()返回`
> - `read()阻塞`, 等待`send()`发送完
>
> TCP的四次挥手过程:
> 1. `客户端`请求断开, `close()阻塞`
> 2. 服务器端发送确认信息(我已知晓)
> 3. 服务器端发送请求信息(请求断开), `close()阻塞`
> 4. `客户端`收到确认信息, 发送确认信息, `close()返回`

假设我们访问一个网页: [http://192.168.0.204:9070/index.html](https://daixll.github.io)

> * 客户端
>   1. 应用层打包数据 `GET /index.html HTTP/1.1` 
>   2. 传输层加上 TCP 头 `TCP` `GET /index.html HTTP/1.1` 
>   3. 网络层加上 IP 头 `IP` `TCP` `GET /index.html HTTP/1.1` 
>   4. 物理层 (数据链路层) 加上 MAC 头 `MAC` `IP` `TCP` `GET /index.html HTTP/1.1` 
> * 服务器端
>   1. 物理层, 解析报头
>   2. 网络层, 解析IP
>   3. 传输层, 解析 TCP (这里实际上会三次握,上层数据只有在建立连接后才带上)
>   4. 应用层, 解析数据 `GET /index.html HTTP/1.1`

此时看来, 百度百科关于Socket的介绍就非常形象了:
>所谓套接字(Socket)，就是对网络中不同主机上的应用进程之间进行双向通信的端点的抽象。
一个套接字就是网络上进程通信的一端，提供了应用层进程利用网络协议交换数据的机制。
从所处的地位来讲，套接字上联应用进程，下联网络协议栈，是应用程序通过网络协议进行通信的接口，是应用程序与网络协议栈进行交互的接口。


* 相关函数
`#include <sys/types.h> 提供类型`
`#include <sys/socket.h> 提供socket函数及数据结构`
`#include <arpa/inet.h> 提供IP地址转换函数`
`#include <unistd.h> 提供close()` 

<details><summary> socket() </summary>

```cpp
int socket(int domain, int type, int protocol);
```
> 创建一个 socket 
> - domain: 协议域
> `AF_INET`: IPV4
> `AF_INET6`: IPV6
> `AD_LOCAL`: 一个绝对路径名
> - type: socket类型
> `SOCK_STREAM`: 流式套接字, TCP协议等
> `SOCK_DGRAM`: 数据包套接字, UDP协议等
> `SOCK_RAW`: 原始套接字, IP/ICMP协议等, 接收发向本机的ICMP、IGMP协议包
> - protocol: 指定协议
> `IPPROTO_TCP`: TCP传输协议
> `IPPTOTO_UDP`: UDP传输协议
> `IPPROTO_SCTP`: SCTP传输协议
> `IPPROTO_TIPC`: TIPC传输协议

```cpp 
int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
// IPV4协议 流式套接字 自动匹配type对应的协议
```
</details> 

<details><summary> bind() </summary>

```cpp
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```
> - sockfd: socket描述字, 给哪个sockfd绑定地址
> - addr: 一个const struct sockaddr *指针, 指向要绑定给sockfd的协议地址
>   ```cpp
>   struct sockaddr_in {            // IPV4
>       sa_family_t    sin_family;  // 协议族
>       struct in_addr sin_addr;    // 地址
>       in_port_t      sin_port;    // 端口
>   };
>   ```
> - addrlen: 地址的长度
```cpp
sockaddr_in serv_addr;
bzero(&serv_addr, sizeof serv_addr);
serv_addr.sin_family      = AF_INET;
serv_addr.sin_addr.s_addr = inet_addr("192.168.0.203");
serv_addr.sin_port        = htons(9070);
bind(serv_sock, (sockaddr*)&serv_addr, sizeof serv_addr);
```
</details>



<details><summary> listen() </summary>

```cpp
int listen(int sockfd, int backlog);
```
> - sockfd: 监听哪个sockfd
> - backlog: 最大连接数

```cpp
listen(serv_sock, 1024);
```
</details>

<details><summary> connect() </summary>

```cpp
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```
> sockfd: 客户端的sockfd
> addr: 服务器的socket地址
> addrlen: 服务器地址的长度
```cpp
connect(clnt_sock, (sockaddr*)&serv_addr, sizeof serv_addr);
```

</details>


<details><summary> accept() </summary>

```cpp
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```
> - sockfd: 服务器的sockfd
> - addr: 客户端的地址
> - addrlen: 客户端地址的长度
```cpp
sockaddr_in clnt_addr;
bzero(&clnt_addr, sizeof clnt_addr);
socklen_t clnt_addr_len = sizeof clnt_addr;
int clnt_sock = accept(serv_sock, (sockaddr*)&clnt_addr, &clnt_addr_len);
```
</details>







<details><summary> recv() </summary>

```cpp
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```
> sockfd: 接受的套接字
> buf: 目标缓冲区
> len: 缓冲区接受字节长度
> flags: 一般为0

```cpp

```
</details>






<details><summary> sendms() </summary>

```cpp
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
```
</details>






<details><summary> close() </summary>

```cpp
int close(int fd);
```
> 这个有点复杂, 后面写
```cpp
close(serv_sock);
```
</details>


```cpp
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string.h>
#include <iostream>

int main(){
    // 创建
    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    // 绑定
    sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof serv_addr);
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.0.203");
    serv_addr.sin_port        = htons(9070);
    bind(serv_sock, (sockaddr*)&serv_addr, sizeof serv_addr);

    // 监听
    listen(serv_sock, 1024);

    // 连接
    sockaddr_in clnt_addr;
    bzero(&clnt_addr, sizeof clnt_addr);
    socklen_t clnt_addr_len = sizeof clnt_addr;
    int clnt_sock = accept(serv_sock, (sockaddr*)&clnt_addr, &clnt_addr_len);

    // 读取
    char s[1000];
    int n = recv(clnt_sock, s, 1024, 0);
    s[n]='\0';
    for(int i=0; s[i]!='0'; i++) putchar(s[i]);

    // 关闭
    close(serv_sock);
    return 0;
}
```