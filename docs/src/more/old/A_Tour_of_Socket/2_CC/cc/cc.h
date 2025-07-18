#pragma once
#include "tool.h"

#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <set>

namespace jiao{
class cc{

/*  所有的提示消息在函数内部输出
 *  所有错误的处理，全部在 start() 中处理   */

public:
    cc(const std::string& ip = "0.0.0.0", const int& port = 10086);
    ~cc();

    void start();   // 开始运行
private:
    // 返回 -1 连接失败
    // 其余为连接成功的套接字
    int conn(const std::string& ip, const int& port);   // 主动连接
    
    // 返回 0 发送失败 对方已经断开
    // 返回 1 发送成功
    bool sendMsg(const int& target, std::string& msg);  // 主动发送
    
    // 返回 -1 再试一次
    // 其余为正常套接字
    int acc();                                          // 被动连接

    // 返回 "" 再试一次
    // 返回 "kill" 对方已经断开
    // 其余为正常消息
    std::string recvMsg(const int& target);             // 被动接收

    void kill();                                        // 清理 kk

    int server;                                         // 服务器套接字
    sockaddr_in server_addr;                            // 服务器地址
    std::set<int> cs;                                   // 连接的客户端 or 服务器
    std::set<int> kk;                                   // 延迟删除
    char buf[1024];                                     // 缓冲区
};
}   // namespace jiao