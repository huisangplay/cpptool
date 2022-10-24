//
// Created by huisa on 2022/10/1.
//

#include <vector>
#include "windowsutil.h"

string OnSigBtnSelectInstallDir() {
    BROWSEINFO bi;
    bi.hwndOwner = NULL;
    bi.pidlRoot = CSIDL_DESKTOP;//�ļ��еĸ�Ŀ¼���˴�Ϊ����
    bi.pszDisplayName = NULL;
    bi.lpszTitle = NULL;//��ʾλ�ڶԻ������ϲ�����ʾ��Ϣ
    bi.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;//���½��ļ��а�ť
    bi.lpfn = NULL;
    bi.iImage = 0;
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);//����ѡ��Ի���
    if (pidl == NULL) {
        return "null";
    }
    TCHAR strFolder[MAX_PATH];
    SHGetPathFromIDList(pidl, strFolder);
    return strFolder;
}

void getAllFiles(string path, vector <string> &files) {
    //�ļ����
    long hFile = 0;
    //�ļ���Ϣ
    struct _finddata_t fileinfo; //�����õ��ļ���Ϣ��ȡ�ṹ
    string p; //string�������˼��һ����ֵ����:assign()���кܶ����ذ汾
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) //�ж��Ƿ�Ϊ�ļ���
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                    getAllFiles(p.assign(path).append("/").append(fileinfo.name), files);//�ݹ鵱ǰ�ļ���
                }
            } else  //�ļ�����
            {
                files.push_back(p.assign(path).append("/").append(fileinfo.name));//�ļ���
            }
        } while (_findnext(hFile, &fileinfo) == 0); //Ѱ����һ�����ɹ�����0������-1
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

vector <string> split(const string &s, char delimiter) {
    vector <string> tokens;
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

string getCurrentYearMonthDayString() {
    time_t curtime;
    time(&curtime);
    tm *nowtime = localtime(&curtime);
    string year = to_string(1900 + nowtime->tm_year);
    string month = to_string(1 + nowtime->tm_mon);
    string day = to_string(nowtime->tm_mday);
    return year + month + day;
}

BOOL CopyToClipboard(const char *pszData, const int nDataLen) {
    if (::OpenClipboard(NULL)) {
        ::EmptyClipboard();
        HGLOBAL clipbuffer;
        char *buffer;
        clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, nDataLen + 1);
        buffer = (char *) ::GlobalLock(clipbuffer);
        strcpy(buffer, pszData);
        ::GlobalUnlock(clipbuffer);
        ::SetClipboardData(CF_TEXT, clipbuffer);
        ::CloseClipboard();
        return TRUE;
    }
    return FALSE;
}

BOOL CopyToClipboard(CString source) {
    if (OpenClipboard(NULL)) {
        //��ֹ��ASCII���Ը��Ƶ����а�Ϊ����
        int buff_size = source.GetLength();
        CStringW strWide = CStringW(source);
        int nLen = strWide.GetLength();
        //�����а��ÿ�
        ::EmptyClipboard();
        HANDLE clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, (nLen + 1) * 2);
        if (!clipbuffer) {
            ::CloseClipboard();
            return FALSE;
        }
        char *buffer = (char *) ::GlobalLock(clipbuffer);
        memset(buffer, 0, (nLen + 1) * 2);
        memcpy_s(buffer, nLen * 2, strWide.GetBuffer(0), nLen * 2);
        strWide.ReleaseBuffer();
        ::GlobalUnlock(clipbuffer);
        ::SetClipboardData(CF_UNICODETEXT, clipbuffer);
        ::CloseClipboard();
        return TRUE;
    }
    return FALSE;
}