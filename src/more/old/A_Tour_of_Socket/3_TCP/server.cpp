#include "Headers/Sock.h"
#include <set>

int main(int argc, char const *argv[]){
    jiao::Sock Server("0.0.0.0", std::atoi(argv[1]));
    Server.Listen();                        // 监听
    
    Server.setNonBlock();                   // 设置非阻塞
    std::set<jiao::Sock*> cs;               // 保存所有连接的套接字

    while(true){
        // 接受连接
        jiao::Sock* Client = Client = Server.Ac();
        if(Client->fd > 0){
            std::cout << "连接成功! Socket: " << Client->fd << std::endl;
            Client->setNonBlock();
            cs.insert(Client);
        }

        for(auto it = cs.begin(); it != cs.end(); ++it){
            std::string msg = (*it)->Recv();
            
            if(msg != ""){
                if(msg == "kill"){
                    std::cout << "Socket: " << (*it)->fd << " 断开连接!" << std::endl;
                    cs.erase(it);
                    delete *it;
                    break;
                }

                std::cout << "收到 " << (*it)->fd << " 的消息: " << msg << std::endl;
                (*it)->Send(msg);
            }
        }
    }

    return 0;
}