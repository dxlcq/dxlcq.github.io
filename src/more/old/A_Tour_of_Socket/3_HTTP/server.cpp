#include "Headers/Sock.h"
#include "Headers/Epoll.h"

int main(int argc, char const *argv[]){
    jiao::Sock* server = new jiao::Sock("0.0.0.0", std::atoi(argv[1]));
    server -> Listen();
    server -> setNonBlock();
    
    jiao::Epoll* epoll = new jiao::Epoll();
    epoll -> Add(server);

    while(true)
    for(auto& c : epoll->Wait())
        if(c->fd == server->fd){                // 有新连接
            jiao::Sock* client = server -> Ac();// 接受一个连接
            client -> setNonBlock();            // 设置非阻塞
            client -> data = new std::string(); // 用于保存数据
            epoll -> Add(client, EPOLLOUT | EPOLLIN | EPOLLET);
        }
        else if(c->ev.events & EPOLLIN){        // 可读事件
            if(std::string msg = c -> Recv(); msg == "kill")
                epoll -> Del(c);
            else if(msg == "")
                continue;
            else{                               // 解析请求 GET / HTTP/1.1
                std::string path = msg.substr(msg.find(' ')+1, msg.find("HTTP")-msg.find(' ')-2);
                if(path == "/") path = "/index.html";
                jiao::log("IN:" + path);

                c -> data -> clear();
                *c -> data = path;

                epoll -> Mod(c, EPOLLOUT | EPOLLET);
            }
        }
        else if(c->ev.events & EPOLLOUT){
            std::string path = *c -> data;
            jiao::log("OUT:" + path);
            c ->Send("HTTP/1.1 200 OK\r\n\r\n" + jiao::get_file("src" + path));
            epoll -> Del(c);
        }
    
    delete server;
    delete epoll;
    return 0;
}