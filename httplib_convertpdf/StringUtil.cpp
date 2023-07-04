//
// Created by ZHOU on 2023/7/3.
//

#include "StringUtil.h"
#include <locale>
#include <codecvt>

std::string stringutil::UTF8_2_GBK(const std::string& utf8String) {
    // 将UTF-8编码的字符串转换为Unicode字符串
    const int wcharLength = MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, nullptr, 0);
    wchar_t* wcharString = new wchar_t[wcharLength];
    MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, wcharString, wcharLength);

    // 将Unicode字符串转换为GBK编码的字符串
    const int gbkLength = WideCharToMultiByte(CP_ACP, 0, wcharString, -1, nullptr, 0, nullptr, nullptr);
    char* gbkString = new char[gbkLength];
    WideCharToMultiByte(CP_ACP, 0, wcharString, -1, gbkString, gbkLength, nullptr, nullptr);

    // 将GBK编码的字符串转换为std::string类型
    std::string result(gbkString);

    // 释放内存
    delete[] wcharString;
    delete[] gbkString;

    return result;
}


wchar_t *stringutil::CharToWChar(const char *str) {
    int length = strlen(str); // 计算原始字符串长度

    // 计算需要的wchar_t数组长度
    int wLength = MultiByteToWideChar(CP_UTF8, 0, str, length, nullptr, 0);

    // 分配wchar_t数组内存
    auto *wStr = new wchar_t[wLength + 1];

    // 转换char数组为wchar_t数组
    MultiByteToWideChar(CP_UTF8, 0, str, length, wStr, wLength);

    // 将wchar_t数组末尾添加结束符
    wStr[wLength] = L'\0';

    // 返回转换后的wchar_t数组
    return wStr;
}