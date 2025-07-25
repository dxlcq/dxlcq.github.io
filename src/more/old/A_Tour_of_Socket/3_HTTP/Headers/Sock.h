#pragma once

#include "Tool.h"
#include "SockAddr.h"
#include "unistd.h"
#include <sys/epoll.h>

#include <fcntl.h>

#define BUFSIZE 1024

namespace jiao{

class Sock
{

public:
    Sock();                                         // 仅创建套接字
    Sock(const std::string& ip, const int& port);   // 创建套接字并绑定
    ~Sock();
    
    void Listen(const int& num=0);                      // 监听
    bool Conn(const std::string& ip, const int& port);  // 主动连接
    Sock* Ac();                                         // 接受一个连接
    // 成功 Sock.fd > 0
    // 失败 Sock.fd < 0

    bool Send(const std::string& msg);                  // 发送
    std::string Recv();                                 // 接收
    // 成功 返回 数据
    // 失败 返回 ""

    void setNonBlock() {                                // 设置非阻塞
        fcntl(fd, F_SETFL, O_NONBLOCK | fcntl(fd, F_GETFL));
        non_block = true;
    }

    std::string*data;   // 用于保存数据
    SockAddr*   addr;   // 套接字地址
    int         fd;     // 套接字

    epoll_event ev;     // epoll 事件
private:
    char*       buf;            // 缓冲区
    bool        buf_init=false; // 缓冲区是否初始化
    bool        non_block=false;// 是否开启非阻塞
};

}   // namespace jiao