#include "../HEADERS/Event.h"

using namespace jiao;

Event::Event(const std::string& ip, const int& port){
    addr = new SockAddr(ip, port);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    err(sock == -1, "创建套接字错误");

    int ret = bind(sock, (sockaddr*)addr->get_addr(), *addr->get_addr_len());
    err(ret == -1, "绑定套接字错误");

    ret = listen(sock, 5);
    err(ret == -1, "监听套接字错误");

    fcntl(sock, F_SETFL, O_NONBLOCK);
}

Event::~Event(){
    delete addr;
    close(sock);
}

std::string Event::recvMsg(const int& client){
    if(cs.count(client) == 0) return "";

    memset(buf, '\0', sizeof buf);
    int len = recv(client, buf, sizeof buf, 0);
    
    if(len == -1) {
        //war(true, "接收数据错误");
        return "";
    }
    else if(len == 0) {
        war(true, "客户端断开连接: " + std::to_string(client));
        close(client);
        return "kill";
    }
    
    return std::string(buf);
}

int Event::sendMsg(const int& client, const std::string& msg){
    if(cs.count(client) == 0) return 0;
    if(msg == "") return -1;

    int len = send(client, msg.c_str(), msg.size(), 0);
    
    if(len == -1) {
        //war(true, "发送数据错误");
        return -1;
    }
    else if(len == 0) {
        war(true, "客户端断开连接: " + std::to_string(client));
        close(client);
        return 0;
    }

    return 1;
}

void Event::loop(std::function<std::string(std::string)> deal){
    acer = new Accepter(sock);

    while(true){
        int client = acer -> ac();
        if(client != -1) {
            fcntl(client, F_SETFL, O_NONBLOCK);
            cs.insert(client);
            log("客户端建立连接: " + std::to_string(client));
        }

        std::set<int> down;

        for(const auto c: cs){
            std::string msg = recvMsg(c);
            if(msg == "")
                continue;
            else if(msg == "kill")
                down.insert(c);
            else if(sendMsg(c, deal(msg)) == 0)
                down.insert(c);
        }

        for(const auto c: down) cs.erase(c);
    }
}