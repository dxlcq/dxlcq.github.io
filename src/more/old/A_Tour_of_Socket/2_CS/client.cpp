// TCP 非阻塞
// 服务端一直接收客户端连接
// 服务端一直接收发送客户端数据
// 服务端用 set 存储所有的客户端，每次循环遍历 set，接收数据
#include "tool.h"

#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <fcntl.h>

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

    // 客户端设置为非阻塞
    fcntl(client, F_SETFL, O_NONBLOCK);
    std::cin.sync_with_stdio(false);  // 关闭同步，准备非阻塞 cin
    char buf[1024];
    while(true){
        // 发送数据
        memset(buf, '\0', sizeof buf);
        
        if(std::cin.rdbuf()->in_avail() > 0)
            std::cin.getline(buf, sizeof buf);
        
        int len = send(client, buf, strlen(buf), 0);
        if(len > 0)
            std::cout << "发送数据成功！\n" << std::endl;
        
        // 接收数据
        memset(buf, '\0', sizeof buf);
        len = recv(client, buf, sizeof buf, 0);
        if(len > 0)
            std::cout << "\n接收数据成功，长度：" << len << "；内容：" << buf << std::endl;
    }

    close(client);
    return 0;
}