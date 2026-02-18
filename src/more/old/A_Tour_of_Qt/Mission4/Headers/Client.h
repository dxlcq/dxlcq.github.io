#pragma once

#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string>

namespace jiao{

class Client{
public:
    void err(bool flg, std::string msg);
    bool war(bool flg, std::string msg);

    Client();   // 初始化
    ~Client();  // 关闭连接

    void sendMsg(std::string msg);  // 发送消息
    std::string recvMsg();          // 接收消息

    int getid();// 获取 id
private:
    char buf[1024]; // 缓冲区
    int client;     // 客户端套接字
    int id;         // 客户端 id
};

} // namespace jiao