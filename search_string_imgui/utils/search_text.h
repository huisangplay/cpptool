//
// Created by 500958 on 2022/10/9.
//
#pragma warning(disable:4996)
#include<string>
#include <vector>

#include<map>
#include<fstream>
#include<iostream>
#include "stringutil.h"
#ifndef SEARCH_STRING_IMGUI_SEARCH_TEXT_H
#define SEARCH_STRING_IMGUI_SEARCH_TEXT_H
bool search_text(std::string file_path, std::string findstr);
bool search_text(std::wstring filepath, std::wstring findstr);
#endif //SEARCH_STRING_IMGUI_SEARCH_TEXT_H
