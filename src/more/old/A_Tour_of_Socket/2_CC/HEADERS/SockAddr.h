#pragma once

#include <arpa/inet.h>
#include "../HEADERS/Tool.h"

namespace jiao{

class SockAddr
{
public:
    SockAddr(const std::string& ip="0.0.0.0", const int& port=10086);
    ~SockAddr();

    sockaddr_in addr;
    socklen_t   addr_len;
};

}   // namespace jiao