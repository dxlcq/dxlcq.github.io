#include "信道.h"

信道::信道(int 描述符, 事件轮询 *事件树){
    this->描述符 = 描述符;
    this->事件树 = 事件树;
}

信道::~信道(){
    事件树->删除事件(描述符, EPOLLIN | EPOLLOUT);
    close(描述符);
}

void 信道::设置非阻塞(bool 非阻塞){
    int 选项 = fcntl(描述符, F_GETFL);
    错误(选项 == -1, "获取描述符选项错误");
    if(非阻塞) 选项 |= O_NONBLOCK;
    else 选项 &= ~O_NONBLOCK;
    错误(fcntl(描述符, F_SETFL, 选项) == -1, "设置描述符选项错误");
}