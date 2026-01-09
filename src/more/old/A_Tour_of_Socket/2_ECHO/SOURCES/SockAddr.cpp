#include "../HEADERS/SockAddr.h"

using namespace jiao;

SockAddr::SockAddr(const std::string& ip, const int& port){
    sock_addr     = new sockaddr_in;
    sock_addr_len = new socklen_t;
    memset(sock_addr, '\0', sizeof *sock_addr);
    
    if(ip == "" || port == 0) return;

    sock_addr->sin_family      = AF_INET;
    sock_addr->sin_addr.s_addr = inet_addr(ip.c_str());
    sock_addr->sin_port        = htons(port);
    *sock_addr_len = sizeof *sock_addr;
}

SockAddr::~SockAddr(){
    delete sock_addr;
    delete sock_addr_len;
}