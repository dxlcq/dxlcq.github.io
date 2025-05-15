#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>

void 错误(bool 标志, std::string 错误信息){
    if(!标志) return ;  // 如果没有错误，直接返回
    std::cerr<<错误信息<<errno;
    exit(0);
}

bool 警告(bool 标志, std::string 警告信息){
    if(!标志) return 0;  // 如果没有警告，返回 0
    std::cerr<<警告信息<<errno;
    return 1;
}

int main(){
    int 服务端 = socket(AF_INET, SOCK_STREAM, 0);
    错误(服务端 == -1, "socket创建错误");
    /*  创建 socket 创建失败会返回 -1

    第一个参数  domain  协议族
        AF_INET     IPV4
        AF_INET6    IPV6
        AD_LOCAL    绝对路径名
    
    第二个参数  type    socket类型   
        SOCK_STREAM 流式套接字      TCP协议等
        SOCK_DGRAM  数据包套接字    UDP协议等
        SOCK_RAW    原始套接字      IP/ICMP协议等
    
    第三个参数  protocol指定协议
        0               自动匹配
        IPPROTO_TCP     TCP传输协议 
        IPPTOTO_UDP     UDP传输协议 
        IPPROTO_SCTP    SCTP传输协议
        IPPROTO_TIPC    TIPC传输协议
    */

    sockaddr_in 服务端地址;
    memset(&服务端地址, 0, sizeof 服务端地址);
    服务端地址.sin_family      = AF_INET;
    服务端地址.sin_addr.s_addr = inet_addr("0.0.0.0");
    服务端地址.sin_port        = htons(8080);
    int 端口复用 = 1;    // 端口复用
    setsockopt(服务端, SOL_SOCKET, SO_REUSEADDR, (const void *)&端口复用, sizeof(端口复用));
    错误(
        bind(服务端, (sockaddr*)&服务端地址, sizeof 服务端地址) == -1,
        "绑定服务端地址错误"
    );
    /*  服务端绑定地址  绑定失败会返回 -1
    
    第一个参数  fd          需要绑定的socket
    
    第二个参数  sockaddr    绑定的地址
        此参数需要传入一个 sockaddr_in 类型，其中
        sin_family      协议族
        sin_addr.s_addr 地址
        sin_port        端口
    
    第三个参数  socklen_t   地址的大小
    */

    错误(
        listen(服务端, 5) == -1,
        "服务端监听错误"
    );
    /* 监听该socket 监听错误会返回 -1
        第一个参数  fd  需要监听的socket
        第二个参数  n   最大连接数量
    */

    while(1){
        sockaddr_in 客户端地址;
        socklen_t 客户端地址大小 = sizeof 客户端地址;
        int 客户端 = accept(服务端, (sockaddr*)&客户端地址, &客户端地址大小);
        if( 警告( 客户端==-1, "接受客户端连接错误") ) continue;
        std::cout<<"\n新的连接："<<客户端<<" IP地址："<<inet_ntoa(客户端地址.sin_addr)<<"\n";
        /*  接受客户端地址连接 接受错误会返回 -1
        第一个参数 fd           服务端
        第二个参数 addr         客户端地址
        第三个参数 addr_len     客户端地址大小
        */

        char 缓冲区[1024];
        while(1){
            // 接收数据
            memset(缓冲区, '\0', sizeof 缓冲区); 
            int 长度 = recv(客户端, 缓冲区, sizeof 缓冲区, 0);
            if(长度 <= 0){
                std::cout<<客户端<<" "<<"客户端断开连接\n";
                close(客户端);
                break;
            }
            std::cout<<"\n接收数据成功，长度:"<<长度<<"；内容："<<缓冲区<<"\n";
            // 输入数据
            memset(缓冲区, '\0', sizeof 缓冲区);
            std::cout<<"输入要发送的数据：";
            std::cin>>缓冲区;
            send(客户端, 缓冲区, strlen(缓冲区), 0);
        }
    }
    close(服务端);
    return 0;
}