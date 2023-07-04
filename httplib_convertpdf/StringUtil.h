//
// Created by ZHOU on 2023/7/3.
//

#ifndef DROGON_CONVERTPDF_STRINGUTIL_H
#define DROGON_CONVERTPDF_STRINGUTIL_H

#include<string>
#include <windows.h>

namespace stringutil {
    std::string UTF8_2_GBK(const std::string& utf8Str);
    // 将UTF-8编码的char数组转换为wchar_t数组
    // str: 需要转换的char数组
    // return: 转换后的wchar_t数组，需要手动释放内存
    wchar_t * CharToWChar(const char *str);
}


#endif //DROGON_CONVERTPDF_STRINGUTIL_H
