#include <iostream>
#include <cstring>
#include <sys/socket.h> 
#include <sys/ioctl.h>      // I/O control 输入输出控制
#include <net/if.h>         // interface interface 接口
#include <arpa/inet.h>      // definitions for internet operations 因特网操作的定义
#include <ifaddrs.h>        // definitions for interface address structures 接口地址结构的定义
#include <unistd.h>
#include <map>

int main() {
    std::map<std::string, std::pair<std::string, std::string>> IPV6; // IPv6地址和子网掩码

    ifaddrs *获取IPv6;
    if (getifaddrs(&获取IPv6) == -1) std::cerr << "获取IPv6信息错误！" << std::endl;
    
    for(ifaddrs *i = 获取IPv6; i!=NULL && i->ifa_name!=NULL; i = i->ifa_next)
        if(i->ifa_addr->sa_family == AF_INET6){ // 如果是 IPv6 地址
            char IPv6地址[INET6_ADDRSTRLEN]; memset(&IPv6地址, 0, sizeof IPv6地址);
            char IPv6掩码[INET6_ADDRSTRLEN]; memset(&IPv6掩码, 0, sizeof IPv6掩码);

            // 获取接口的IPv6地址
            void* 地址 = &((sockaddr_in6*)i->ifa_addr)->sin6_addr;
            // 获取接口的IPv6子网掩码
            void* 掩码 = &((sockaddr_in6*)i->ifa_netmask)->sin6_addr;

            if(inet_ntop(AF_INET6, 地址, IPv6地址, INET6_ADDRSTRLEN) != NULL)
                IPV6[i->ifa_name].first = IPv6地址;
            if(inet_ntop(AF_INET6, 掩码, IPv6掩码, INET6_ADDRSTRLEN) != NULL)
                IPV6[i->ifa_name].second = IPv6掩码;   
        }

    int 套接字 = socket(AF_INET, SOCK_STREAM, 0);   // 创建套接字
    if (套接字 < 0) {
        std::cerr<<"创建套接字错误！"<<std::endl;
        return 1;
    }

    /*  ifreq：Interface Request
    struct ifreq {
        char ifr_name[IFNAMSIZ];  // 网络接口名称
        union {
            struct sockaddr ifr_addr;      // IPv4地址
            struct sockaddr ifr_netmask;   // 子网掩码
            struct sockaddr ifr_dstaddr;   // 目标地址
            struct sockaddr ifr_broadaddr; // 广播地址
            struct sockaddr ifr_hwaddr;    // MAC地址
            short           ifr_flags;     // 接口标志（状态）
            int             ifr_ifindex;   // 接口索引
            int             ifr_metric;    // 接口的度量值
            int             ifr_mtu;       // 最大传输单元（MTU）
            // ... 可能还有其他成员
        } ifr_ifru;
    };
    */           

    struct if_nameindex *首个网络接口 = if_nameindex();
    if (首个网络接口 == NULL) {
        std::cerr<<"获取网络接口错误！"<<std::endl;
        return 1;
    }

    for(auto i=首个网络接口; i->if_index!=0 && i->if_name!=NULL; i++){
        ifreq 网络接口信息;
        memset(&网络接口信息, 0, sizeof 网络接口信息);
        strcpy(网络接口信息.ifr_name, i->if_name); // 设置网络接口名称

        // 获取接口的名称
        std::cout<<"\n\n"<<i->if_name<<"：\n";

        // 获取接口的MAC地址
        if (ioctl(套接字, SIOCGIFHWADDR, &网络接口信息) == 0) {
            char mac[18];
            snprintf(mac, sizeof(mac), "%02x:%02x:%02x:%02x:%02x:%02x",
                     (unsigned char)网络接口信息.ifr_hwaddr.sa_data[0],
                     (unsigned char)网络接口信息.ifr_hwaddr.sa_data[1],
                     (unsigned char)网络接口信息.ifr_hwaddr.sa_data[2],
                     (unsigned char)网络接口信息.ifr_hwaddr.sa_data[3],
                     (unsigned char)网络接口信息.ifr_hwaddr.sa_data[4],
                     (unsigned char)网络接口信息.ifr_hwaddr.sa_data[5]);
            printf("%-24s %s\n", "    物理地址：", mac);
        }

        // 获取接口的IPv6地址
        printf("%-22s %s\n", "    IPv6 地址：", IPV6[i->if_name].first.c_str());

        // 获取接口的IPv6子网掩码
        printf("%-22s %s\n", "    IPv6 子网掩码：", IPV6[i->if_name].second.c_str());

        // 获取接口的IPv4地址
        if (ioctl(套接字, SIOCGIFADDR, &网络接口信息) == 0)
            printf("%-22s %s\n", "    IPv4 地址：", inet_ntoa(((sockaddr_in *)&网络接口信息.ifr_addr)->sin_addr));
        
        // 获取接口的IPv4子网掩码
        if (ioctl(套接字, SIOCGIFNETMASK, &网络接口信息) == 0)
            printf("%-22s %s\n", "    IPv4 子网掩码：", inet_ntoa(((sockaddr_in *)&网络接口信息.ifr_netmask)->sin_addr));
        
        // 获取接口的IPv4广播地址
        if (ioctl(套接字, SIOCGIFBRDADDR, &网络接口信息) == 0)
            printf("%-22s %s\n", "    IPv4 广播地址：", inet_ntoa(((sockaddr_in *)&网络接口信息.ifr_broadaddr)->sin_addr));

        // 获取接口的IPv4目标地址
        if (ioctl(套接字, SIOCGIFDSTADDR, &网络接口信息) == 0)
            printf("%-22s %s\n", "    IPv4 目标地址：", inet_ntoa(((sockaddr_in *)&网络接口信息.ifr_dstaddr)->sin_addr));

        // 获取接口的最大传输单元（MTU）
        if (ioctl(套接字, SIOCGIFMTU, &网络接口信息) == 0)
            printf("%-22s %d\n", "    MTU：", 网络接口信息.ifr_mtu);

        // 获取接口的接口索引
        if (ioctl(套接字, SIOCGIFINDEX, &网络接口信息) == 0)
            printf("%-22s %d\n", "    接口索引：", 网络接口信息.ifr_ifindex);


        // 获取接口的接口标志（状态）
        if (ioctl(套接字, SIOCGIFFLAGS, &网络接口信息) == 0) {
            printf("%-22s ", "    接口标志：");
            if (网络接口信息.ifr_flags & IFF_UP) printf("UP ");
            if (网络接口信息.ifr_flags & IFF_BROADCAST) printf("BROADCAST ");
            if (网络接口信息.ifr_flags & IFF_DEBUG) printf("DEBUG ");
            if (网络接口信息.ifr_flags & IFF_LOOPBACK) printf("LOOPBACK ");
            if (网络接口信息.ifr_flags & IFF_POINTOPOINT) printf("POINTOPOINT ");
            if (网络接口信息.ifr_flags & IFF_RUNNING) printf("RUNNING ");
            if (网络接口信息.ifr_flags & IFF_NOARP) printf("NOARP ");
            if (网络接口信息.ifr_flags & IFF_PROMISC) printf("PROMISC ");
            if (网络接口信息.ifr_flags & IFF_NOTRAILERS) printf("NOTRAILERS ");
            if (网络接口信息.ifr_flags & IFF_ALLMULTI) printf("ALLMULTI ");
            if (网络接口信息.ifr_flags & IFF_MASTER) printf("MASTER ");
            if (网络接口信息.ifr_flags & IFF_SLAVE) printf("SLAVE ");
            if (网络接口信息.ifr_flags & IFF_MULTICAST) printf("MULTICAST ");
            if (网络接口信息.ifr_flags & IFF_PORTSEL) printf("PORTSEL ");
            if (网络接口信息.ifr_flags & IFF_AUTOMEDIA) printf("AUTOMEDIA ");
            if (网络接口信息.ifr_flags & IFF_DYNAMIC) printf("DYNAMIC ");
            printf("\n");
        }

        // 获取接口的度量值
        if (ioctl(套接字, SIOCGIFMETRIC, &网络接口信息) == 0)
            printf("%-22s %d\n", "    度量值：", 网络接口信息.ifr_metric);

    }

    if_freenameindex(首个网络接口);
    close(套接字);

    return 0;
}
