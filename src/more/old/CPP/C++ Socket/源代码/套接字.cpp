#include "套接字.h"

套接字::套接字(std::string IP, int 端口号){
    // 创建套接字
    描述符 = socket(AF_INET, SOCK_STREAM, 0);
    错误(描述符 == -1, "创建套接字错误");
    // 端口复用
    int 端口复用 = 1;
    错误(setsockopt(描述符, SOL_SOCKET, SO_REUSEADDR, &端口复用, sizeof 端口复用) == -1, "端口复用错误");
    // 绑定套接字
    地址.sin_family = AF_INET;
    地址.sin_addr.s_addr = inet_addr(IP.c_str());
    地址.sin_port = htons(端口号);
    地址长度 = sizeof 地址;
    错误(bind(描述符, (sockaddr*)&地址, 地址长度) == -1, "绑定套接字错误");
}

套接字::~套接字(){
    close(描述符);  // 关闭套接字
}

void 套接字::设置非阻塞(bool 非阻塞){
    int 标志 = fcntl(描述符, F_GETFL, 0);   // 获取描述符标志
    if(非阻塞) 标志 |= O_NONBLOCK;          // 设置非阻塞
    else 标志 &= ~O_NONBLOCK;               // 设置阻塞
    fcntl(描述符, F_SETFL, 标志);           // 设置描述符标志
}

void 套接字::开始监听(int 最大连接数){
    错误(listen(描述符, 最大连接数) == -1, "监听错误");
}

int 套接字::接受连接(){
    int 客户端 = accept(this->描述符, (sockaddr*)&地址, &地址长度);
    警告(客户端 == -1, "接受连接错误");
    return 客户端;
}