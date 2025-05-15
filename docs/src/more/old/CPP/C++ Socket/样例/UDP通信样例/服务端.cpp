#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>

int main(){
    sockaddr_in 服务端地址, 客户端地址; memset(&客户端地址, 0, sizeof 客户端地址);
    服务端地址.sin_family       = AF_INET;                  // IPv4
    服务端地址.sin_addr.s_addr  = inet_addr("172.25.94.149");   // IP
    服务端地址.sin_port         = htons(8081);              // 端口
    
    int 服务端 = socket(AF_INET, SOCK_DGRAM, 0);            // 1. 创建套接字
    bind(服务端, (sockaddr*)&服务端地址, sizeof 服务端地址);  // 2. 绑定套接字
    
    socklen_t 客户端地址长度 = sizeof 客户端地址;
    while(1){
        char 缓冲区[1024]; memset(缓冲区, 0, sizeof 缓冲区); // 3. 接收数据
        recvfrom(服务端, 缓冲区, sizeof 缓冲区, 0, (sockaddr*)&客户端地址, &客户端地址长度);
        std::cout<<缓冲区<<std::endl;                       // 4. 发送数据
        sendto(服务端, "我已收到", strlen("我已收到"), 0, (sockaddr*)&客户端地址, sizeof 客户端地址);    
    }
    return 0;
}