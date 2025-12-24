#include "../Headers/Tool.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

using namespace jiao;

void jiao::err(bool flg, const std::string& msg){
    if(!flg) return ;   // 如果没有错误，直接返回
    std::cerr << RED << "\n" + msg + " 错误代码: " << errno << RESET << std::endl;
    exit(1);
}

bool jiao::war(bool flg, const std::string& msg){
    if(!flg) return 0;  // 如果没有警告，返回 0
    std::cerr << YELLOW << "\n" + msg + " 警告代码: " << errno << RESET << std::endl;
    return 1;
}

void jiao::log(const std::string& msg){
    std::cerr << "\n" << msg << std::endl;
}

std::string jiao::get_file(const std::string& path){
    std::ifstream ifs(path);
    if(!ifs.is_open()){
        log("文件打开失败: " + path);
        return "";
    }
    std::stringstream ss;   // 用于存储文件内容
    ss << ifs.rdbuf();      // 将文件内容读入 ss
    return ss.str();
}