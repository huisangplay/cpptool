//
// Created by huisa on 2022/10/1.
//

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