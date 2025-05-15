/*  一个物理socket可以对应多个channel(信道）
    每个channel是个虚拟socket。
    线程调用channel执行网络IO.
    这种模式可以减少SOCKET的创建，在大并发系统对系统稳定有作用。    */
#pragma once

#include "事件轮询.h"
#include "套接字.h"

class 信道{
public:
    信道(int 描述符, 事件轮询 *事件树);
    ~信道();

    void 设置非阻塞(bool 非阻塞=true);

    void 添加事件(int 类型){ 事件树->添加事件(描述符, 类型);};
    void 修改事件(int 类型){ 事件树->修改事件(描述符, 类型);};
    void 删除事件(int 类型){ 事件树->删除事件(描述符, 类型);};

    int 获取描述符(){ return 描述符; };
private:
    int 描述符;
    事件轮询 *事件树;
    
};