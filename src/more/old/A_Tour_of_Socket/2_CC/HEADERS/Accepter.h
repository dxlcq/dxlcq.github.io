#pragma once

#include "SockAddr.h"

namespace jiao{

// 接收器
class Accepter
{
public:
    Accepter(const int& sock);
    ~Accepter();

    int ac();                   // 获取客户端的 socket (接收一次)
private:
    int         _server_sock;   // 服务端的 socket (接受者)
    SockAddr*   _client_addr;   // 客户端的地址
};

}   // namespace jiao