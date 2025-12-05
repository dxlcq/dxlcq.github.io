#include "../HEADERS/Conn.h"

using namespace jiao;

Conn::Conn(const std::string& ip, const int& port){
    SockAddr* _server_addr = new SockAddr(ip, port);
    _server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(war(_server_sock == -1, "连接器: 创建套接字错误!"))
        return;

    if(connect(_server_sock, (sockaddr*)&_server_addr->addr, _server_addr->addr_len) == -1){
        war(true, "连接器: 连接 " + ip + ":" + std::to_string(port) + " 失败!");
        close(_server_sock);
        return;
    }

    log("连接器: 连接 " + ip + ":" + std::to_string(port) + " 成功!");
}

Conn::~Conn(){
    //close(_server_sock);
}

int Conn::getSock() const{
    return _server_sock;
}