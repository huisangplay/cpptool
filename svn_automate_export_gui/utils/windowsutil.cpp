//
// Created by huisa on 2022/10/1.
//

#include <vector>
#include "windowsutil.h"
string OnSigBtnSelectInstallDir()
{
    BROWSEINFO bi;
    bi.hwndOwner = NULL;
    bi.pidlRoot = CSIDL_DESKTOP;//文件夹的根目录，此处为桌面
    bi.pszDisplayName = NULL;
    bi.lpszTitle = NULL;//显示位于对话框左上部的提示信息
    bi.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;//有新建文件夹按钮
    bi.lpfn = NULL;
    bi.iImage = 0;
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);//调用选择对话框
    if (pidl == NULL)
    {
        return "null";
    }
    TCHAR strFolder[MAX_PATH];
    SHGetPathFromIDList(pidl, strFolder);
    return strFolder;
}
void getAllFiles(string path, vector<string> &files) {
    //文件句柄
    long hFile = 0;
    //文件信息
    struct _finddata_t fileinfo; //很少用的文件信息读取结构
    string p; //string类很有意思的一个赋值函数:assign()，有很多重载版本
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) //判断是否为文件夹
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                    getAllFiles(p.assign(path).append("/").append(fileinfo.name), files);//递归当前文件夹
                }
            } else  //文件处理
            {
                files.push_back(p.assign(path).append("/").append(fileinfo.name));//文件名
            }
        } while (_findnext(hFile, &fileinfo) == 0); //寻找下一个，成功返回0，否则-1
        _findclose(hFile);
    }
}

string checkPathType(string path) {
    string typecmd = "if not exist \"" + path + "\"  ( @echo INVALID ) else if exist " + path +
                     "\\nul ( @echo FOLDER) else ( @echo FILE)";
    return cmdProcess(typecmd.c_str());
}
string cmdProcess(const char *cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool createDirectory(const std::string folder) {
    std::string folder_builder;
    std::string sub;
    sub.reserve(folder.size());
    for (auto it = folder.begin(); it != folder.end(); ++it) {
        const char c = *it;
        sub.push_back(c);
        if (c == '\\' || it == folder.end() - 1) {
            folder_builder.append(sub);
            if (0 != ::_access(folder_builder.c_str(), 0)) {
                // this folder not exist
                if (0 != ::_mkdir(folder_builder.c_str())) {
                    // create failed
                    return false;
                }
            }
            sub.clear();
        }
    }
    return true;
}
string getCurrentYearMonthDayString(){
    time_t curtime;
    time(&curtime);
    tm* nowtime=localtime(&curtime);
    string year= to_string(1900+nowtime->tm_year);
    string month= to_string(1+nowtime->tm_mon);
    string day= to_string(nowtime->tm_mday);
    return year+month+day;
}

BOOL CopyToClipboard(const char* pszData, const int nDataLen) {
    if (::OpenClipboard(NULL)) {
        ::EmptyClipboard();
        HGLOBAL clipbuffer;
        char* buffer;
        clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, nDataLen + 1);
        buffer = (char*)::GlobalLock(clipbuffer);
        strcpy(buffer, pszData);
        ::GlobalUnlock(clipbuffer);
        ::SetClipboardData(CF_TEXT,clipbuffer);
        ::CloseClipboard();
        return TRUE;
    }
    return FALSE;
}