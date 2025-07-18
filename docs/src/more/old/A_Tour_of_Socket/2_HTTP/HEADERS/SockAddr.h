#pragma once

#include <arpa/inet.h>
#include "../HEADERS/Tool.h"

namespace jiao{

class SockAddr
{
public:
    SockAddr(const std::string& ip="0.0.0.0", const int& port=10086);
    ~SockAddr();

    sockaddr_in* get_addr() const { return sock_addr; }
    socklen_t*   get_addr_len() const { return sock_addr_len; }

private:
    sockaddr_in* sock_addr;
    socklen_t*   sock_addr_len;
};

}   // namespace jiao