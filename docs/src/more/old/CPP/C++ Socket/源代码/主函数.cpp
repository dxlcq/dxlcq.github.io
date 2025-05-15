#include "工具.h"
#include "套接字.h"
#include "事件轮询.h"
#include <thread>

加载配置文件 *配置文件 = new 加载配置文件();

void 处理请求(int 客户端){
    if(客户端 == 0) return;
    std::string 请求;
    char 缓冲区[102400];
    while(1){
        memset(缓冲区, 0, sizeof 缓冲区);
        int 长度 = recv(客户端, 缓冲区, sizeof 缓冲区, 0);
        if(长度 > 0){
            std::cout<<"【"<<客户端<<"】"<<"长度："<<长度<<" ";
            请求 += 缓冲区;
        } else if(长度 == -1 && errno == EINTR){    // 信号中断返回，没有任何数据可用，正常，继续
            continue;
        } else if(长度 == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){  
            break;
        } else if(长度 == 0){
            std::cout<<"【"<<客户端<<"】断开连接\n";
            close(客户端);
            break;
        }
    }
    // 解析目标文件
    std::string 目标文件 = "";
    int i=0;
    while(i<请求.size() && 请求[i] != ' ') i++;
    i+=2;
    while(i<请求.size() && 请求[i] != ' ') 目标文件 += 请求[i++];
    if(目标文件 == "") 目标文件 = "index.html";
    else 目标文件 = url_decode(目标文件);
    // 读取文件
    std::string 文件内容;
    long long 文件长度 = 读取文件(配置文件->配置项["网页文件路径"] + 目标文件, 文件内容);
    // 发送响应
    std::string 响应头 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(文件长度) + "\r\n\r\n";
    send(客户端, 响应头.c_str(), 响应头.size(), 0);

    std::cout<<"目标文件大小 "<<文件内容.size()<<"\n";
    // 分批发送文件
    const char* 现在 = 文件内容.c_str();
    int 失败次数=0;
    while(文件长度 !=0 && 失败次数 < 10){
        long long 实际发送 = send(客户端, 现在, std::min(文件长度, (long long)102400), 0);
        if(实际发送 < 0){
            警告(实际发送 == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK)), "发送错误" + 目标文件);
            sleep(1);
            失败次数++;
            continue;
        }
        现在 += 实际发送;
        文件长度 -= 实际发送;
    }
    close(客户端);
}

void 接受连接(套接字 *服务端, 事件轮询 *事件树){
    int 客户端 = 服务端->接受连接();
    fcntl(客户端, F_SETFL, fcntl(客户端, F_GETFL) | O_NONBLOCK);
    事件树->添加事件(客户端, EPOLLIN | EPOLLET);
}

int main(){
    套接字 *服务端 = new 套接字(配置文件->配置项["IP地址"], std::stoi(配置文件->配置项["端口号"]));
    事件轮询 *事件树 = new 事件轮询();
    
    服务端->设置非阻塞();
    服务端->开始监听();
    事件树->添加事件(服务端->获取描述符(), EPOLLIN | EPOLLET);
    
    //std::vector<std::thread> 线程池;
    //for(int i=0; i<4; i++)  // 启动四个线程
    //    线程池.push_back(std::thread(处理请求, 0));

    // 开始接收连接
    std::vector<epoll_event> 事件;
    while(1){
        事件 = 事件树->等待事件();
        for(auto i: 事件)
            if(i.data.fd == 服务端->获取描述符())
                std::thread(接受连接, 服务端, 事件树).detach();
            else if(i.events & EPOLLIN)     // 可读事件
                std::thread(处理请求, (int)i.data.fd).detach();
            /*
                for(int j=0; j<线程池.size(); j++)
                    if(!线程池[j].joinable()){
                        线程池[j] = std::thread(处理请求, (int)i.data.fd);
                        break;              // 找到一个空闲线程就退出
                    }
            */
    }

    delete 服务端;
    delete 事件树;
    return 0;
}