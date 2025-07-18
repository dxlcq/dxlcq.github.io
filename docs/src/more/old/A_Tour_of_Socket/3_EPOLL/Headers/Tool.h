#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

namespace jiao{

void err(bool flg, const std::string& msg);
bool war(bool flg, const std::string& msg);
void log(const std::string& msg);
std::string get_file(const std::string& path);

}   // namespace jiao