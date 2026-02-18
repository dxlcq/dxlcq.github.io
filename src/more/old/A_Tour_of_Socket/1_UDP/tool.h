#pragma once
#include <iostream>
#include <string>

void err(bool flg, std::string msg){
    if(!flg) return ;   // 如果没有错误，直接返回
    std::cerr << "\n" << msg << "\n错误代码：" << errno << std::endl;
    exit(1);
}

bool war(bool flg, std::string msg){
    if(!flg) return 0;  // 如果没有警告，返回 0
    std::cerr << "\n" << msg << "\n警告代码：" << errno << std::endl;
    return 1;
}