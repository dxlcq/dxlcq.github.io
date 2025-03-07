#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>

int main(){
    sockaddr_in 服务端地址, 客户端地址;
    服务端地址.sin_family       = AF_INET;                  // IPv4
    服务端地址.sin_addr.s_addr  = inet_addr("127.0.0.1");   // IP 
    服务端地址.sin_port         = htons(8080);              // 端口

    int 客户端 = socket(AF_INET, SOCK_DGRAM, 0);    // 1. 创建套接字
    while(1){
        char 缓冲区[1024]; std::cin>>缓冲区;         // 2. 发送数据
        sendto(客户端, 缓冲区, strlen(缓冲区), 0, (sockaddr*)&服务端地址, sizeof 服务端地址);
        //memset(缓冲区, 0, sizeof 缓冲区);            // 3. 接收数据
        std::cout<<"完成输入"<<std::endl;
        recvfrom(客户端, 缓冲区, sizeof 缓冲区, 0, NULL, NULL);
        std::cout<<缓冲区<<std::endl;
        std::cout<<"完成接收"<<std::endl;
    }
    return 0;
}