#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <sys/epoll.h>
#include <fcntl.h>

#include <string.h>
#include <iostream>
#include <string>

void 错误(bool 标志, std::string 错误信息){
    if(!标志) return ;  // 如果没有错误，直接返回
    std::cerr<<错误信息<<errno<<"\n";
    exit(0);
}

bool 警告(bool 标志, std::string 警告信息){
    if(!标志) return 0;  // 如果没有警告，返回 0
    std::cerr<<警告信息<<errno<<"\n";
    return 1;
}

int 套接字(std::string IP地址, int 端口){
    int 😂 = socket(AF_INET, SOCK_STREAM, 0);
    错误(😂 == -1, "socket创建错误");

    sockaddr_in 地址;
    memset(&地址, 0, sizeof 地址);
    地址.sin_family      = AF_INET;
    地址.sin_addr.s_addr = inet_addr(IP地址.c_str());
    地址.sin_port        = htons(端口);
    int 端口复用 = 1;    // 端口复用
    setsockopt(😂, SOL_SOCKET, SO_REUSEADDR, (const void *)&端口复用, sizeof 端口复用);
    错误( bind(😂, (sockaddr*)&地址, sizeof 地址) == -1,
        "绑定服务端地址错误" );
    fcntl(😂, F_SETFL, O_NONBLOCK); // 设置为非阻塞模式
    return 😂;
}

void 连接客户端(int 服务端, int 事件树){
    sockaddr_in 客户端地址;
    memset(&客户端地址, 0, sizeof 客户端地址);
    socklen_t 客户端地址大小 = sizeof 客户端地址;
    
    int 客户端 = accept(服务端, (sockaddr*)&客户端地址, &客户端地址大小);
    if( 警告( 客户端==-1, "接受客户端连接错误") ) return;
    fcntl(客户端, F_SETFL, O_NONBLOCK); // 设置为非阻塞模式
    /* 客户端连接信息 */
    std::cout<<"【"<<客户端<<"】"<<"新的连接"<<" ip："<<inet_ntoa(客户端地址.sin_addr)<<"\n---\n";

    epoll_event 事件;
    memset(&事件, 0, sizeof 事件);

    事件.data.fd = 客户端;  // 监听客户端
    事件.events = EPOLLIN | EPOLLET;  // 可写事件
    错误( epoll_ctl(事件树, EPOLL_CTL_ADD, 客户端, &事件) == -1,
        "客户端注册事件错误" );
}

void 接收数据(int 客户端, int 事件树){
    char 缓冲区[10240];
    while(1){
        memset(缓冲区, 0, sizeof 缓冲区);
        int 长度 = recv(客户端, 缓冲区, sizeof 缓冲区, 0);
        if(长度 > 0){
            std::cout<<"【"<<客户端<<"】"<<"长度："<<长度<<"内容："<<缓冲区<<"\n";
        } else if(长度 == -1 && errno == EINTR){
            std::cout<<"【"<<客户端<<"】"<<"信号中断\n";
            continue;
        } else if(长度 == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){  
            std::cout<<"【"<<客户端<<"】"<<"没有数据可用\n";
            epoll_event 事件;
            memset(&事件, 0, sizeof 事件);
            事件.data.fd = 客户端;
            事件.events = EPOLLOUT | EPOLLET;
            epoll_ctl(事件树, EPOLL_CTL_MOD, 客户端, &事件);
            break;
        } else if(长度 == 0){
            std::cout<<"【"<<客户端<<"】断开连接\n";
            epoll_ctl(事件树, EPOLL_CTL_DEL, 客户端, NULL);
            close(客户端);
            break;
        } else if(长度 == -1){
            std::cout<<"【"<<客户端<<"】"<<"未知错误\n";
            epoll_ctl(事件树, EPOLL_CTL_DEL, 客户端, NULL);
            close(客户端);
            break;
        }
    }
    return ;
}

void 发送数据(int 客户端, int 事件树){
    std::string 缓冲区="HTTP/1.1 200 OK\r\n\r\n我已收到😀";
    int 长度 = send(客户端, 缓冲区.c_str(), 缓冲区.size(), 0);    
    警告(长度 == -1, "发送数据错误");

    //close(客户端);
    epoll_event 事件;
    memset(&事件, 0, sizeof 事件);
    事件.data.fd = 客户端;
    事件.events = EPOLLIN | EPOLLET;
    epoll_ctl(事件树, EPOLL_CTL_MOD, 客户端, &事件);
    return ;
}

int main(){
    int 服务端 = 套接字("127.0.0.1", 8080);
    错误( listen(服务端, 1024) == -1, "监听错误" );

    int 事件树 = epoll_create1(0);
    错误( 事件树 == -1, "epoll创建错误" );

    epoll_event 事件; 
    memset(&事件, 0, sizeof 事件);

    事件.data.fd = 服务端;            // 监听服务端
    事件.events = EPOLLET | EPOLLIN; // 监听可读事件
    错误( epoll_ctl(事件树, EPOLL_CTL_ADD, 服务端, &事件) == -1,
        "服务端注册事件错误" );

    epoll_event 就绪事件[102400];
    while(1){
        int 事件数量 = epoll_wait(事件树, 就绪事件, 102400, -1);
        错误(事件数量 == -1, "事件树等待错误");

        for(int i=0; i<事件数量; i++)
            if(就绪事件[i].data.fd == 服务端)
                连接客户端(服务端, 事件树);
            else if(就绪事件[i].events & EPOLLIN)
                接收数据(就绪事件[i].data.fd, 事件树);
            else if(就绪事件[i].events & EPOLLOUT)
                发送数据(就绪事件[i].data.fd, 事件树);
    }

    return 0;
}