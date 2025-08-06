// UDP
// 客户端发送一条数据，接收一条数据
// 服务端接收一条数据，发送一条数据
#include "tool.h"

#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    int server = socket(AF_INET, SOCK_DGRAM, 0);
    err(server == -1, "socket创建错误");

    sockaddr_in server_addr;
    memset(&server_addr, '\0', sizeof server_addr);
    server_addr.sin_family       = AF_INET;
    server_addr.sin_addr.s_addr  = inet_addr("127.0.0.1");
    server_addr.sin_port         = htons(10086);

    char buf[1024];
    while(true){
        // 发送数据
        memset(buf, '\0', sizeof buf);
        std::cout << "输入要发送的数据：";
        std::cin >> buf;
        if( war( 
                sendto(server, buf, strlen(buf), 0, (sockaddr*)&server_addr, sizeof server_addr) == -1,
                "发送数据错误") )
            continue;
        else
            std::cout << "发送数据成功！\n" << std::endl;
        
        // 接收数据
        memset(buf, '\0', sizeof buf);
        sockaddr_in client_addr;
        memset(&client_addr, '\0', sizeof client_addr);
        socklen_t client_addr_len = sizeof client_addr;      
        int len = recvfrom(server, buf, sizeof buf, 0, (sockaddr*)&client_addr, &client_addr_len);
        if(len == -1){
            std::cout << "接收数据错误" << std::endl;
            continue;
        } else
            std::cout << "\n接收数据成功，长度：" << len << "；内容：" << buf << std::endl;
    }

    close(server);
    return 0;
}