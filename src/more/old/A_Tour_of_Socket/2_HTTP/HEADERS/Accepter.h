#pragma once

#include <fcntl.h>

#include "SockAddr.h"

namespace jiao{

class Accepter
{
public:
    Accepter(const int& sock);
    ~Accepter();

    int ac();   // 获取客户端的 socket
private:
    int sock;   // 服务端的 socket
    SockAddr* client_addr;
};

}   // namespace jiao