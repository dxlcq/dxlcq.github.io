#pragma once

#include "工具.h"

#include <sys/epoll.h> // epoll套件
#include <unistd.h>    // close()
#include <vector>
#include <string.h>

class 事件轮询{
public:
    事件轮询();
    ~事件轮询();

    void 添加事件(int 描述符, int 类型);
    void 修改事件(int 描述符, int 类型);
    void 删除事件(int 描述符, int 类型);

    std::vector<epoll_event> 等待事件(int 最大事件数=4096, int 超时时间=-1);
private:
    int 描述符;
    epoll_event 事件表[102400];
};