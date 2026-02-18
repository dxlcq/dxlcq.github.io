#include "事件轮询.h"

事件轮询::事件轮询(){
    描述符 = epoll_create1(0);
    错误(描述符 == -1, "创建epoll错误");
}

事件轮询::~事件轮询(){
    close(描述符);
}

std::vector<epoll_event> 事件轮询::等待事件(int 最大事件数, int 超时时间){
    memset(事件表, 0, sizeof 事件表);
    int 事件数 = epoll_wait(描述符, 事件表, 最大事件数, 超时时间);
    错误(事件数 == -1, "epoll等待错误");
    std::vector<epoll_event> 返回事件表(事件数);
    for(int i=0; i<事件数; i++) 返回事件表[i] = 事件表[i];
    return 返回事件表;
}

void 事件轮询::添加事件(int 描述符, int 类型){
    epoll_event 事件;
    memset(&事件, 0, sizeof 事件);
    事件.data.fd = 描述符;
    事件.events = 类型;
    错误(epoll_ctl(this->描述符, EPOLL_CTL_ADD, 描述符, &事件) == -1, "epoll添加事件错误");
}

void 事件轮询::修改事件(int 描述符, int 类型){
    epoll_event 事件;
    memset(&事件, 0, sizeof 事件);
    事件.data.fd = 描述符;
    事件.events = 类型;
    错误(epoll_ctl(this->描述符, EPOLL_CTL_MOD, 描述符, &事件) == -1, "epoll修改事件错误");
}

void 事件轮询::删除事件(int 描述符, int 类型){
    epoll_event 事件;
    memset(&事件, 0, sizeof 事件);
    事件.data.fd = 描述符;
    事件.events = 类型;
    错误(epoll_ctl(this->描述符, EPOLL_CTL_DEL, 描述符, &事件) == -1, "epoll删除事件错误");
}