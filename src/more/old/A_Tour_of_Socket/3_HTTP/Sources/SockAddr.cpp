#include "../Headers/SockAddr.h"

using namespace jiao;

SockAddr::SockAddr(const std::string& ip, const int& port){
    memset(&addr, '\0', sizeof addr);
    addr_len = sizeof addr;
    if(ip == "" || port == 0) return;   // 仅创建套接字地址

    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port        = htons(port);
    addr_len = sizeof addr;
}

SockAddr::~SockAddr(){}