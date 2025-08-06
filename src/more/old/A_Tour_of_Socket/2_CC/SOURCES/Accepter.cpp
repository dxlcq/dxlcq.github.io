#include "../HEADERS/Accepter.h"

using namespace jiao;

Accepter::Accepter(const int& sock): _server_sock(sock){
    _client_addr = new SockAddr("", 0);
}

Accepter::~Accepter(){
    delete _client_addr;
}

int Accepter::ac(){
    memset(&_client_addr->addr, '\0', sizeof _client_addr->addr);
    _client_addr->addr_len = sizeof _client_addr->addr;
    int ret = accept(_server_sock, (sockaddr*)&_client_addr->addr, &_client_addr->addr_len);

    if(ret == -1){
        if(errno != EAGAIN)
            war(true, "接收器: 接收客户端失败!");
        return ret;
    }
    else
        std::cout << inet_ntoa(_client_addr->addr.sin_addr) << ":" << ntohs(_client_addr->addr.sin_port) << " 已连接! Socket: " << ret << std::endl;

    return ret;
}