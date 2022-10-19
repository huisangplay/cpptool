#include<vector>
#include <direct.h>
#include <io.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include<vector>
#include <iostream>
#include<algorithm>
#include<filesystem>
#include <io.h>
#include <direct.h>
#include<fstream>
#include <sstream>
#include <shlobj.h>
#include<ctime>
using namespace std;
string OnSigBtnSelectInstallDir();
void getAllFiles(string path, vector<string> &files);
string checkPathType(string path);
string cmdProcess(const char *cmd);
bool createDirectory(const std::string folder);
string getCurrentYearMonthDayString();
BOOL CopyToClipboard(const char* pszData, const int nDataLen);