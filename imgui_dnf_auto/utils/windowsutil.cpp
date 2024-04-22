//
// Created by huisa on 2022/10/1.
//
#define UNICODE
#include <string>
#include <shlobj.h>
#include "windowsutil.h"
#include <Windows.h>
#include <iostream>
using namespace std;
BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam)
{
    // 获取窗口标题长度
    int length = GetWindowTextLength(hwnd);
    if (length == 0)
        return TRUE;

    // 申请缓冲区获取窗口标题
    WCHAR* buffer = new WCHAR[length + 1];
    GetWindowText(hwnd, buffer, length + 1);

    // 将窗口标题与目标窗口名称进行比较
    const WCHAR* targetTitle = reinterpret_cast<const WCHAR*>(lParam);
    if (wcscmp(buffer, targetTitle) == 0)
    {
        // 找到匹配的窗口，设置为活动窗口
        std::wcout << L"Found window: " << buffer << std::endl;
        SetForegroundWindow(hwnd);
        delete[] buffer;
        return FALSE; // 停止枚举
    }

    delete[] buffer;
    return TRUE;
}

void SetActiveWindowByName(const WCHAR* windowName)
{
    EnumWindows(EnumWindowsCallback, reinterpret_cast<LPARAM>(windowName));
}