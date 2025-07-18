#pragma once 

#include "Tool.h"
#include "SockAddr.h"
#include <fcntl.h>
#include <unistd.h>

namespace jiao{

// 连接器
class Conn
{
public:
    Conn(const std::string& ip, const int& port);
    ~Conn();

    int getSock() const;
private:
    int         _server_sock;   // 服务端的 socket
};

}   // namespace jiao