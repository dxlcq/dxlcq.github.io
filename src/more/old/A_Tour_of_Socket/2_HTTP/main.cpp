#include "HEADERS/Event.h"

std::string deal(std::string msg){
    // 获取请求行
    std::string line = msg.substr(0, msg.find("\r\n"));
    // 获取请求地址
    std::string path = line.substr(line.find(" ") + 2, line.rfind(" ") - line.find(" ") - 2);
    if(path == "") path = "index.html";
    path = "src/" + path;

    std::string file = jiao::get_file(path);
    // 打包请求头
    std::string head = "HTTP/1.1 200 OK\r\n";
    head += "Content-Type: text/html\r\n";
    head += "Content-Length: " + std::to_string(file.size()) + "\r\n";
    head += "\r\n";
    head += file;

    return head;
} // 服务器接收 HTTP 请求，返回 HTTP 响应

int main(int argc, char const *argv[]){
    jiao::Event* s = new jiao::Event("0.0.0.0", atoi(argv[1]));
    s->loop(deal);
    delete s;
    return 0;
}