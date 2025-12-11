#pragma once

#include <unistd.h>
#include <sys/epoll.h>
#include <vector>
#include <map>
#include "Sock.h"
#include "Tool.h"

#define MAXEVENTS 1024

namespace jiao{

class Epoll
{
public:
    Epoll();
    ~Epoll();

    // 添加事件
    void Add(Sock* sock, const int& new_event=EPOLLIN | EPOLLET);
    // 修改事件
    void Mod(Sock* sock, const int& new_event);
    // 删除事件
    void Del(Sock* sock);

    // 获取事件
    std::vector<Sock*> Wait();
private:
    int epoll_fd;                   // epoll 也是有一个文件描述符的
    std::map<int, Sock*> sock_map;  // 用于保存套接字
};

}   // namespace jiao