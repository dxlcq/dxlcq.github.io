#pragma once   

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

void 错误(bool 标志, std::string 错误信息);

bool 警告(bool 标志, std::string 警告信息);

long long 读取文件(const std::string 文件名, std::string &内容);

class 加载配置文件{
public:
    加载配置文件(std::string 配置文件名="配置文件.txt");
    ~加载配置文件();
    std::map<std::string, std::string> 配置项;
};

std::string url解码(std::string url);

std::string url_decode(const std::string& url);