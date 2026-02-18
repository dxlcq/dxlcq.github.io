#include "工具.h"

void 错误(bool 标志, std::string 错误信息){
    if(!标志) return ;  // 如果没有错误，直接返回
    std::cerr<<RED<<错误信息<<" "<<errno<<RESET<<"\n";
    exit(0);
}

bool 警告(bool 标志, std::string 警告信息){
    if(!标志) return 0;  // 如果没有警告，返回 0
    std::cerr<<YELLOW<<警告信息<<" "<<errno<<RESET<<"\n";
    return 1;
}

long long 读取文件(const std::string 文件名, std::string &内容){
    std::ifstream 文件(文件名); // 定义文件流
    if(警告(!文件.is_open(), "打开文件错误 " + 文件名)) return -1;
    std::stringstream 缓冲区;   // 定义缓冲区
    缓冲区 << 文件.rdbuf();     // 读取文件内容到缓冲区
    内容 = 缓冲区.str();        // 将缓冲区内容转换为字符串
    return 内容.size();         // 返回文件大小
}


std::string url解码(std::string url){
    std::string 解码后的url = "";
    for(int i=0; i<url.size(); i++){
        if(url[i] == '%'){
            解码后的url += (char)std::stoi(url.substr(i+1, 2), 0, 16);
            i += 2;
        } else if(url[i] == '+'){
            解码后的url += ' ';
        } else {
            解码后的url += url[i];
        }
    }
    return 解码后的url;
}


std::string url_decode(const std::string& url) {
    std::stringstream decoded;
    for (std::size_t i = 0; i < url.size(); ++i) {
        if (url[i] == '%') {
            if (i + 2 < url.size()) {
                std::istringstream iss(url.substr(i + 1, 2));
                int value;
                if (iss >> std::hex >> value) {
                    decoded << static_cast<char>(value);
                    i += 2;
                } else {
                    decoded << url[i];
                }
            } else {
                decoded << url[i];
            }
        } else if (url[i] == '+') {
            decoded << '+';
        } else {
            decoded << url[i];
        }
    }
    return decoded.str();
}


加载配置文件::加载配置文件(std::string 配置文件名){
    std::string 配置文件内容;
    long long 配置文件长度 = 读取文件(配置文件名, 配置文件内容);
    int i=0;
    while(i<配置文件长度){
        std::string 配置名 = "", 配置值 = "";
        while(i<配置文件长度 && 配置文件内容[i] != '=')
            配置名 += 配置文件内容[i++];
        i++;
        while(i<配置文件长度 && 配置文件内容[i] != '\n')
            配置值 += 配置文件内容[i++];
        i++;
        配置项[配置名] = 配置值;
    }
}

加载配置文件::~加载配置文件(){}