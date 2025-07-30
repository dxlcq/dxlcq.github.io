#include <iostream>
#include <regex>
#include <cstring>
#include <chrono>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
//#include <sys/socket.h>
//#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

const int N = 256;

inline bool 域名(const char *IP){
    std::regex r("([a-zA-Z0-9]+\\.){1,}[a-zA-Z0-9]+");
    return std::regex_match(IP, r);
}

inline bool IPv4(const char *IP){
    std::regex r("([0-9]{1,3}\\.){3}[0-9]{1,3}");
    return std::regex_match(IP, r);
}

inline bool IPv6(const char *IP){
    std::regex r("^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$");
    return std::regex_match(IP, r);
}

inline bool 获取域名的IPv4地址(const char *域名, char *IPv4地址){
    addrinfo 目标地址信息, *结果;
    memset(&目标地址信息, 0, sizeof 目标地址信息);
    目标地址信息.ai_family = AF_INET;              
    目标地址信息.ai_socktype = SOCK_STREAM;

    if(getaddrinfo(域名, NULL, &目标地址信息, &结果) != 0){
        std::cerr<<"获取 "<<域名<<" 的 IPv4 地址失败\n";
        return 0;
    }

    sockaddr_in *IPv4地址信息 = (sockaddr_in*)结果->ai_addr;
    inet_ntop(AF_INET, &IPv4地址信息->sin_addr, IPv4地址, INET_ADDRSTRLEN); // 将网络字节序转换为点分十进制
    freeaddrinfo(结果);

    return 1;
}

inline bool 获取域名的IPv6地址(const char *域名, char *IPv6地址){
    // TODO
    return 0;
}

struct 报文{
    icmphdr 头部;
    char 数据[36];
};

unsigned short 计算校验和(unsigned short *缓冲区, int 长度){
    unsigned long 和 = 0;
    while(长度 > 1){        // 将数据以16位为单位累加到累加和中
        和 += *缓冲区++;    // 将当前16位块的数据加入累加和
        长度 -= 2;          // 更新剩余数大小，将长度减少2个字节
    }
    if(长度==1) 和 += *(unsigned char*)缓冲区; // 如果剩余一个字节，将其视为16位数据的低8位，加入累加和
    和 = (和 >> 16) + (和 & 0xffff);          // 将32位和的高16位与低16位相加 
    和 += (和 >> 16);                         // 将高16位与低16位相加 
    return (unsigned short)(~和);             // 将相加的结果取反
}

inline void 探测v4(const char *IP, const int 探测次数 = 3){
    std::cout<<"正在探测 "<<IP<<" 具有 64 字节的数据：\n";

    // 1. 创建原始套接字
    int 套接字 = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);   // 创建原始套接字
    if (套接字 < 0) {
        std::cerr<<"创建套接字错误！（是不是忘记 sudo 啦~😊）"<<std::endl;
        return;
    }
    // 设置超时选项
    timeval 超时时间;
    超时时间.tv_sec = 1;
    超时时间.tv_usec = 0;
    if(setsockopt(套接字, SOL_SOCKET, SO_RCVTIMEO, &超时时间, sizeof 超时时间) < 0){
        std::cerr<<"设置超时选项错误！"<<std::endl;
        return;
    }

    // 2. 设置 ICMP报文
    报文 ICMP报文; memset(&ICMP报文, 0, sizeof ICMP报文);
    ICMP报文.头部.type = ICMP_ECHO;             // 对应 8
    ICMP报文.头部.code = 0;                     //
    ICMP报文.头部.un.echo.id = htons(getpt());  //
    ICMP报文.头部.un.echo.sequence = 0;         //
    
    // 获取当前毫秒级别的时间戳
    auto 当前时间 = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
    std::sprintf(ICMP报文.数据, "%ld", 当前时间);  // 将时间戳转换为字符串并放入 ICMP 报文中

    ICMP报文.头部.checksum = 计算校验和((unsigned short *)&ICMP报文, sizeof ICMP报文);

    // 3. 设置 目标地址信息
    sockaddr_in 目标地址信息; memset(&目标地址信息, 0, sizeof 目标地址信息);
    目标地址信息.sin_family = AF_INET;
    inet_pton(AF_INET, IP, &目标地址信息.sin_addr);
    

    for(int _=1; _<=探测次数; _++){

        // 4. 发送 ICMP报文
        int 发送字节数 = sendto(套接字, &ICMP报文, sizeof ICMP报文, 0, (sockaddr*)&目标地址信息, sizeof 目标地址信息);
        if(发送字节数 < 0){
            std::cerr<<"发送 ICMP报文 错误！"<<std::endl;
            return;
        }

        // 5. 接收 ICMP报文
        char 接收缓冲区[N]; memset(接收缓冲区, 0, sizeof 接收缓冲区);
        sockaddr_in 发送者地址信息; memset(&发送者地址信息, 0, sizeof 发送者地址信息);
        socklen_t 发送者地址信息长度 = sizeof 发送者地址信息;
        int 接收字节数 = recvfrom(套接字, 接收缓冲区, sizeof 接收缓冲区, 0, (sockaddr*)&发送者地址信息, &发送者地址信息长度);
        auto 接收时间 = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
        if(接收字节数 == -1){
            std::cout<<"请求超时\n";
            continue;
        }
        
        // 6. 解析 ICMP报文
        char 发送者IP[N]; memset(发送者IP, 0, sizeof 发送者IP);
        inet_ntop(AF_INET, &发送者地址信息.sin_addr, 发送者IP, sizeof 发送者IP);
        std::cout<<发送者IP<<"： 字节="<<接收字节数<<" 时间="<<接收时间-当前时间<<"ms \n";

        当前时间 = 接收时间 + 1000;
        sleep(1);
    }

    // 7. 关闭套接字
    close(套接字);
}

inline void 探测v6(const char *IP){
    // TODO
}

void solve(const char *IP){
    // 判断 IP 类型
    if(IPv4(IP)) 探测v4(IP);
    else if(IPv6(IP)) 探测v6(IP);
    else if(域名(IP)){
        // 获取域名的 IPv4 地址
        char IPv4地址[N]; memset(IPv4地址, 0, sizeof IPv4地址);
        if(获取域名的IPv4地址(IP, IPv4地址)){
            std::cout<<IP<<" 的 IPv4 地址是 "<<IPv4地址<<"\n";
            探测v4(IPv4地址);
        }
        
        // 获取域名的 IPv6 地址
        char IPv6地址[N]; memset(IPv6地址, 0, sizeof IPv6地址);
        if(获取域名的IPv6地址(IP, IPv6地址)){
            std::cout<<IP<<" 的 IPv6 地址是 "<<IPv6地址<<"\n";
            探测v6(IPv6地址);
        }
    }
    else
        std::cout<<"哥们，你这个 ", IP, " 不太对吧？\n";
}

int main(int 命令数量, char *命令行参数[]){
    if(命令数量 < 2){
        std::cerr<<"不是，哥们？干嘛呐，麻烦你输一下IP，v4，v6，域名都行啊！"<<std::endl;
        return 1;
    }
    for(int i=1; i<命令数量; i++, puts("\n")) solve(命令行参数[i]);
    return 0;
}