#pragma once   

#include "工具.h"

#include <sys/socket.h> // socket套件
#include <arpa/inet.h>  // IP套件
#include <unistd.h>     // close()
#include <fcntl.h>      // 设置非阻塞

class 套接字{
public:
    套接字(std::string IP="127.0.0.1", int 端口号=8080);
    ~套接字();

    void 设置非阻塞(bool 非阻塞=true);
    void 开始监听(int 最大连接数=1024);
    int 接受连接();

    int 获取描述符(){ return 描述符; };
private:
    int         描述符;
    sockaddr_in 地址;
    socklen_t   地址长度;
};