#include "../Headers/Client.h"

using namespace jiao;

Client::Client(){
    // 初始化
    client = socket(AF_INET, SOCK_STREAM, 0);
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

    // 接收 id
    id = std::stoi(recvMsg());

    fcntl(client, F_SETFL, O_NONBLOCK); // 客户端设置为非阻塞
    std::cin.sync_with_stdio(false);    // 关闭同步，准备非阻塞 cin
}

Client::~Client(){
    close(client);
}

void Client::sendMsg(std::string msg){
    send(client, msg.c_str(), msg.size(), 0);
}

std::string Client::recvMsg(){
    memset(buf, '\0', sizeof buf);
    int len = recv(client, buf, sizeof buf, 0);
    if(len == -1) return "";
    return std::string(buf);
}

int Client::getid(){
    return id;
}

void Client::err(bool flg, std::string msg){
    if(!flg) return ;   // 如果没有错误，直接返回
    std::cerr << "\n" << msg << "\n错误代码：" << errno << std::endl;
    exit(1);
}

bool Client::war(bool flg, std::string msg){
    if(!flg) return 0;  // 如果没有警告，返回 0
    std::cerr << "\n" << msg << "\n警告代码：" << errno << std::endl;
    return 1;
}