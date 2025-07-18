// TCP
// 客户端发送一条数据，接收一条数据
// 服务端接收一条数据，发送一条数据
#include "tool.h"

#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    int client = socket(AF_INET, SOCK_STREAM, 0);
    err(client == -1, "socket创建错误");
    
    sockaddr_in server_addr;
    memset(&server_addr, '\0', sizeof server_addr);
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port        = htons(10086);
    
    err(
        connect(client, (sockaddr*)&server_addr, sizeof server_addr) == -1,
        "连接服务端错误"
    );
    
    char buf[1024];
    while(true){
        // 发送数据
        memset(buf, '\0', sizeof buf);
        std::cout << "输入要发送的数据：";
        std::cin >> buf;
        if( war(send(client, buf, strlen(buf), 0) <= 0, "发送数据错误") ){
            close(client);
            break;
        }
        else
            std::cout << "发送数据成功！\n" << std::endl;

        // 接收数据
        memset(buf, '\0', sizeof buf);        
        int len = recv(client, buf, sizeof buf, 0);
        if( war(len <= 0, "接收数据错误") ){
            close(client);
            break;
        } else 
            std::cout << "\n接收数据成功，长度：" << len << "；内容：" << buf << std::endl;
    }

    close(client);
    return 0;
}