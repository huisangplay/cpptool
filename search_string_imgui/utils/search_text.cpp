//
// Created by 500958 on 2022/10/9.
//
#include <codecvt>
#include "search_text.h"
bool search_text(std::string filepath, std::string findstr) {
    std::vector<std::wstring> woutput_filepaths;
    std::wstring wfindstr= string2wstring(findstr);
    std::wstring wfilepath= string2wstring(filepath);
    return search_text(wfilepath,wfindstr);
}
bool search_text(std::wstring filepath, std::wstring findstr) {
    std::wstring linestr;

    std::wifstream file_text_chs(filepath, std::ios::binary);
    file_text_chs.imbue(std::locale("chs"));
    if (file_text_chs.is_open())
    {
        while (getline(file_text_chs, linestr))
        {
            const std::wstring temp = linestr;
            if (linestr.find(findstr, 0) != std::wstring::npos) {
                file_text_chs.close();
                file_text_chs.clear();
                return true;
            }
        }
        file_text_chs.close();
        file_text_chs.clear();
    }

    std::wifstream file_text(filepath, std::ios::binary);
    file_text.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    if (file_text.is_open())
    {
        while (getline(file_text, linestr))
        {
            const std::wstring temp = linestr;
            if (linestr.find(findstr, 0) != std::wstring::npos) {
                file_text.close();
                file_text.clear();
                return true;
            }
        }
        file_text.clear();
        file_text.close();
    }
    return false;
}