#include "cc.h"

namespace jiao{

cc::cc(const std::string& ip, const int& port){
    server = socket(AF_INET, SOCK_STREAM, 0);
    err(server == -1, "创建 server 套接字失败!");
    fcntl(server, F_SETFL, O_NONBLOCK); // 设置为非阻塞
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    server_addr.sin_port        = htons(port);
    
    err(
        bind(server, (sockaddr*)&server_addr, sizeof server_addr) == -1,
        "绑定 server 套接字失败!"
    );

    err(
        listen(server, 0) == -1,
        "监听 server 套接字失败!"
    );

    std::cin.sync_with_stdio(false);    // 关闭同步，准备非阻塞 cin
};

cc::~cc(){
    close(server);
};

void cc::start(){
    std::string s;
    while(true){
        if(std::cin.rdbuf() -> in_avail() > 0){                     // 根据输入的指令, 主动连接 or 主动发送
            std::getline(std::cin, s);                              // 一直保持被动连接

            if(std::string flg = s.substr(0, 4); flg == "quit")     
                break;              // 主动退出
            else if(flg == "kill")  // 主动断开
                kk.insert(std::stoi(s.substr(5, s.find(" ", 5) - 5)));
            else if(flg == "find")  // 查看已建立连接
                for(const auto& c : cs) std::cout << c << std::endl;
            else if(flg == "conn"){ // 主动连接
                std::string ip = s.substr(5, s.find(" ", 5) - 5);   // 获取 ip
                int port = std::stoi(s.substr(s.find(" ", 5) + 1)); // 获取 port
                int cc = conn(ip, port);
                if(cc != -1) cs.insert(cc);
            }
            else if(flg == "send"){ // 主动发送
                std::string target = s.substr(5, s.find(" ",5) - 5);// 获取 target
                std::string msg = s.substr(s.find(" ", 5) + 1);     // 获取 msg

                sendMsg(std::stoi(target), msg);
            }
            else                    // 指令错误
                std::cout << "指令错误!" << std::endl;
        }

        // 被动连接
        if(int cc = acc(); cc != -1) cs.insert(cc);
    
        // 被动接收
        kill();
        for(const auto& c : cs){
            std::string msg = recvMsg(c);
            if(msg != "" && msg != "kill")
                std::cout << "接收到 " << c << " 的消息：" << msg << std::endl;
        }
    }
};

void cc::kill(){
    for(const auto& k : kk){
        cs.erase(k);
        close(k);
    }
    kk.clear(); // 清空 kk
};

int cc::conn(const std::string& ip, const int& port){
    std::cout << "正在连接 " << ip << ":" << port << " ..." << std::endl;

    int cc = socket(AF_INET, SOCK_STREAM, 0);
    err(cc == -1, "创建 cc 套接字失败!");

    sockaddr_in cc_addr;
    memset(&cc_addr, 0, sizeof cc_addr);
    cc_addr.sin_family      = AF_INET;
    cc_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    cc_addr.sin_port        = htons(port);

    if(connect(cc, (sockaddr*)&cc_addr, sizeof cc_addr) == 0){
        std::cout << "连接 " << ip << ":" << port << " 成功! Socket:" << cc << std::endl;
        fcntl(cc, F_SETFL, O_NONBLOCK); // 设置为非阻塞
        return cc;
    }
    
    std::cout << "连接 " << ip << ":" << port << " 失败!" << std::endl;
    close(cc);
    return -1;
};

bool cc::sendMsg(const int& target, std::string& msg){
    std::cout << "正在发送 " << msg << " 给 " << target << " ..." << std::endl;
    
    int len = send(target, msg.c_str(), msg.size(), 0);
    
    if(len == 0){
        std::cout << "连接 " << target << " 断开!" << std::endl;
        kk.insert(target);
        return 0;
    }
    
    std::cout << "发送给 " << target << " 成功!" << std::endl;
    return 1;
};

std::string cc::recvMsg(const int& target){
    memset(buf, 0, sizeof buf);
    
    int len = recv(target, buf, sizeof buf, 0);
    
    if(len == -1 && errno == EAGAIN)
        return "";
    else if(len == 0){
        std::cout << "连接 " << target << " 断开!" << std::endl;
        kk.insert(target);
        return "kill";
    }
    else
        return buf;
};

int cc::acc(){
    sockaddr_in client_addr;
    socklen_t   client_addr_len = sizeof client_addr;
    memset(&client_addr, 0, sizeof client_addr);

    int cc = accept(server, (sockaddr*)&client_addr, &client_addr_len);
    
    if(cc != -1){
        std::cout << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << " 成功连接! Socket:" << cc << std::endl;
        fcntl(cc, F_SETFL, O_NONBLOCK); // 设置为非阻塞
    }
    return cc;
}

}   // namespace jiao