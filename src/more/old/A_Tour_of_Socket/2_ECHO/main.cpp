#include "HEADERS/Event.h"

std::string deal(std::string msg){
    return msg;
} // 服务器不做任何处理，直接返回客户端发来的消息

int main(int argc, char const *argv[]){
    jiao::Event* s = new jiao::Event("0.0.0.0", atoi(argv[1]));
    s->loop(deal);
    delete s;
    return 0;
}