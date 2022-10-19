//
// Created by huisa on 2022/10/1.
//

#ifndef IMGUI_STRINGUTIL_H
#define IMGUI_STRINGUTIL_H

#endif //IMGUI_STRINGUTIL_H
#include <string>
#include <windows.h>
#include<vector>

using namespace std;
string GBK_2_UTF8(string gbkStr);
string UTF8_2_GBK(string utf8Str);
string remove_surplus_spaces(const string &src);
vector<string> split(const string &s, char delimiter);