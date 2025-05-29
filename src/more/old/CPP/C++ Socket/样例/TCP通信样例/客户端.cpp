#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
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
    int 客户端 = socket(AF_INET, SOCK_STREAM, 0);
    错误(客户端 == -1, "socket创建错误");
    
    sockaddr_in 服务端地址;
    memset(&服务端地址, 0, sizeof 服务端地址);
    服务端地址.sin_family      = AF_INET;
    服务端地址.sin_addr.s_addr = inet_addr("192.168.31.101");
    服务端地址.sin_port        = htons(8080);
    错误(
        connect(客户端, (sockaddr*)&服务端地址, sizeof 服务端地址) == -1,
        "连接服务端错误"
    );
    /*  客户端连接服务端 连接失败返回-1
    第一个参数  fd      连接用的客户端
    第二个参数  addr    目标服务端地址
    第三个参数  len     目标服务端地址大小
    */

    char 缓冲区[1024];
    while(1){
        // 输入数据
        memset(缓冲区, '\0', sizeof 缓冲区);
        std::cout<<"输入要发送的数据：";
        std::cin>>缓冲区;
        if(strcmp(缓冲区, "quit")==0) break;
        send(客户端, 缓冲区, strlen(缓冲区), 0);
        // 接收数据
        memset(缓冲区, '\0', sizeof 缓冲区);
        int 长度 = recv(客户端, 缓冲区, sizeof 缓冲区, 0);
        std::cout<<"\n接收数据成功，长度:"<<长度<<"；内容："<<缓冲区<<"\n";
    }
    close(客户端);
    return 0;
}