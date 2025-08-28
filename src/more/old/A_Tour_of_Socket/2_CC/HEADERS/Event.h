#pragma once

#include <functional>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <set>
#include <regex>

#include "Tool.h"
#include "SockAddr.h"
#include "Accepter.h"

namespace jiao{

class Event
{

public:
    Event(const std::string& ip="0.0.0.0", const int& port=10086);
    ~Event();
    void loop(std::function<std::string(std::string)> deal);

private:
    std::set<int> cs;   // 存活的客户端
    std::set<int> ds;   // 待删除的客户端
    Accepter* acer;     // 接收器

    // 收到消息 正常返回
    // 断开连接 返回 "kill"
    // 稍后重试 返回 ""
    std::string recvMsg(const int& client);
    // 发送消息 成功返回 1
    // 失败返回 0
    // 稍后重试 返回 -1
    int         sendMsg(const int& client, const std::string& msg);
    char buf[1024];

    int         sock;
    SockAddr*   addr;
};

}