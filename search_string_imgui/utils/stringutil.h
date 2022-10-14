//
// Created by huisa on 2022/10/1.
//

#ifndef IMGUI_STRINGUTIL_H
#define IMGUI_STRINGUTIL_H

#endif //IMGUI_STRINGUTIL_H
#include <string>
#include <windows.h>
#include<vector>
#include<sstream>
std::string GBK_2_UTF8(std::string gbkStr);
std::string UTF8_2_GBK(std::string utf8Str);
std::string wstring2string(std::wstring wstr);
std::wstring string2wstring(std::string str);
std::vector<std::string> split(const std::string &s, char delimiter);
std::string remove_surplus_spaces(const std::string &src);
void string_replace( std::string &strBig, const std::string &strsrc, const std::string &strdst);