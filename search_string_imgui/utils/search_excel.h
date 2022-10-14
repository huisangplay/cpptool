//
// Created by 500958 on 2022/10/9.
//
#include "libxl.h"
#include<string>
#include <vector>
using namespace libxl;
#ifndef SEARCH_STRING_IMGUI_SEARCH_EXCEL_H
#define SEARCH_STRING_IMGUI_SEARCH_EXCEL_H

bool search_excel_xls(std::string filepath, std::string findstr);
bool search_excel_xlsx(std::string filepath, std::string findstr);
bool search_excel(std::string filepath, std::string findstr, Book* book);
void setLibxlKey(Book* book);

#endif //SEARCH_STRING_IMGUI_SEARCH_EXCEL_H
