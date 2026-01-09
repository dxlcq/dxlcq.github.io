#include "../HEADERS/Event.h"
#include "../HEADERS/Conn.h"

using namespace jiao;

Event::Event(const std::string& ip, const int& port){
    addr = new SockAddr(ip, port);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    err(-1 == sock,
        "创建套接字错误");

    err(-1 == bind(sock, (sockaddr*)&addr->addr, addr->addr_len),
        "绑定套接字错误");

    err(-1 == listen(sock, 0),
        "监听套接字错误");

    fcntl(sock, F_SETFL, O_NONBLOCK);   // 服务器设置为非阻塞
}

Event::~Event(){
    delete addr;
    close(sock);
}

std::string Event::recvMsg(const int& client){
    memset(buf, '\0', sizeof buf);
    int len = recv(client, buf, sizeof buf, 0);
    
    if(len == -1 && errno == EAGAIN)
        return "";
    else if(len == 0) {
        war(true, "接收时: 客户端断开连接: " + std::to_string(client));
        return "kill";
    }

    return buf;
}

int Event::sendMsg(const int& client, const std::string& msg){
    int len = send(client, msg.c_str(), msg.size(), 0);
    
    if(len == 0) {
        war(true, "发送时: 客户端断开连接: " + std::to_string(client));
        ds.insert(client);
        return 0;
    }

    return 1;
}

void Event::loop(std::function<std::string(std::string)> deal){
    acer = new Accepter(sock);

    std::cin.sync_with_stdio(false);
    std::string s;
    while(true){
        // 接收输入的数据，主动连接或者发送数据
        if(std::cin.rdbuf() -> in_avail() > 0){ // 如果输入缓冲区有数据
            std::getline(std::cin, s);          // 读取数据
            if(std::string flg = s.substr(0, 5); flg == "quit ")
                break;                          // 主动退出
            else if(flg == "kill "){            // 主动断开
                std::string target = s.substr(5, s.find(" ", 5) - 5);
                
                if(std::regex_match(target, std::regex("[0-9]+")) && cs.find(std::stoi(target)) != cs.end())
                    ds.insert(std::stoi(target));
                else// 验证目标的合法性
                    war(true, "kill: 无效的目标: " + target);
            }
            else if (flg.substr(0, 4) == "find")// 查看已建立连接
                for(const auto& c : cs) std::cout << c << std::endl;
            else if (flg == "conn "){           // 主动连接
                std::string ip = s.substr(5, s.find(" ", 5) - 5);
                if(!std::regex_match(ip, std::regex("([0-9]{1,3}\\.){3}[0-9]{1,3}"))){
                    war(true, "conn: 无效的 ip: " + ip);
                    continue;
                }   // 验证 ip 的合法性
                int port = std::stoi(s.substr(s.find(" ", 5) + 1));
                if(port < 0 || port > 65535){
                    war(true, "conn: 无效的 port: " + std::to_string(port));
                    continue;
                }   // 验证 port 的合法性
                
                // 使用 Conn 类连接
                
                jiao::Conn conn(ip, port);
                int _server_sock = conn.getSock();
                if(_server_sock == -1) continue;
                

                // 手动连接 ok
                /*
                SockAddr* _server_addr = new SockAddr(ip, port);
                int _server_sock = socket(AF_INET, SOCK_STREAM, 0);
                if(war(_server_sock == -1, "连接器: 创建套接字错误!"))
                    continue;
                
                if(connect(_server_sock, (sockaddr*)&_server_addr->addr, _server_addr->addr_len) == -1){
                    war(true, "连接器: 连接 " + ip + ":" + std::to_string(port) + " 失败!");
                    close(_server_sock);
                    continue;
                }
                
                log("连接 " + ip + ":" + std::to_string(port) + " 成功! Socket: " + std::to_string(_server_sock));
                */
                
                fcntl(_server_sock, F_SETFL, O_NONBLOCK); // 设置为非阻塞
                cs.insert(_server_sock);
            } else if (flg == "send "){          // 主动发送
                std::string target = s.substr(5, s.find(" ", 5) - 5);
                if(!std::regex_match(target, std::regex("[0-9]+")) || cs.find(std::stoi(target)) == cs.end()){
                    war(true, "send: 无效的目标: " + target);
                    continue;
                }   // 验证目标的合法性
                std::string msg = s.substr(s.find(" ", 5) + 1);

                if(sendMsg(std::stoi(target), msg) == 0)
                    ds.insert(std::stoi(target));
            } else 
                std::cout << "指令错误！" << std::endl;
        }

        // 断开连接
        if(!ds.empty()){
            for(const auto& d : ds){
                cs.erase(d);
                close(d);
            }
            ds.clear(); // 清空 ds
        }

        // 持续接收客户端连接
        if(int cc = acer->ac(); cc != -1){
            fcntl(cc, F_SETFL, O_NONBLOCK); // 新连接设置为非阻塞
            cs.insert(cc);
        }

        // 持续接收客户端消息
        for(const auto& c : cs){
            std::string msg = recvMsg(c);
            if(msg == "kill") ds.insert(c);
            else if(msg == "") continue;
            else
                std::cout << "接收到 " << c << " 的消息：" << msg << std::endl;
        }
    }
}