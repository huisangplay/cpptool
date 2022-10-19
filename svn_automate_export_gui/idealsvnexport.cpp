#include "idealsvnexport.h"
void ideal_svn_export(vector<int>& svn_nums,string submit_path,vector<string>& exportfilelist){
    setlocale(LC_ALL, "zh_CN");

    for (int svn_num: svn_nums) {
        cout<<svn_num<<"123"<<endl;
        getIDEALSvnInfoAndDownloadFilesFromCmd(svn_num,submit_path);
    }

    vector<string> filelist;

    getAllFiles(submit_path+"\\项目代码", filelist);

    int subcount=submit_path.size();

    ofstream outfile(submit_path+"\\ideal_export_file_list.txt", ios::out);
    for (int svn_num: svn_nums) {
        outfile << svn_num << " ";
    }
    outfile << endl;
    for (auto file: filelist) {
        string comparefile = file.substr(subcount);
        replace(comparefile.begin(), comparefile.end(), '\\', '/');
        outfile << comparefile<< endl;
        exportfilelist.push_back( comparefile);
    }
    outfile.flush();
    outfile.close();
    cout << "svn导出位置："+submit_path << endl;
    cout << "svn导出文件列表位置："+submit_path+"\\ideal_export_file_list.txt" << endl;
    cout<<"svn文件导出完成...."<<endl;
}

void getIDEALSvnInfoAndDownloadFilesFromCmd(int version,string submit_path) {
    cout << "开始导出svn:" << version << endl;
    string showdiffcmd = "svn diff -r " + to_string(version - 1) + ":" + to_string(version) +
                         " --summarize http://vcs.comac.intra/svn/sadri/项目代码";

    string changeListResult = cmdProcess(showdiffcmd.c_str());

    vector<string> changeList = split(changeListResult, '\n');
    for (int i = 0; i < changeList.size(); ++i) {

        string change = changeList.at(i);
        vector<string> changeInfoList = split(remove_surplus_spaces(change), ' ');

        string action = changeInfoList.at(0);
        if(action=="") {
            continue;
        }
        string path = "/项目代码" + changeInfoList.at(1).substr(69);
        string svnExportPath = "http://vcs.comac.intra/svn/sadri" + path;
        string exportPath = submit_path + path;

        if (action == "D") {
            replace(exportPath.begin(), exportPath.end(), '/', '\\');
            string type= checkPathType(exportPath);
            string delcmd;
            if (type == "FILE\n") {
                delcmd = "del " + exportPath;
            } else if (type == "FOLDER\n") {
                delcmd = "rd /s /q " + exportPath;
            } else {
                continue;
            }
            cmdProcess(delcmd.c_str());
            cout << "删除路径:" << exportPath << endl;
        } else {
            //导出前先建立文件夹，否则导出失败
            string exportPath = submit_path + path;
            string folderPath = exportPath.substr(0, exportPath.find_last_of("/"));

            replace(folderPath.begin(), folderPath.end(), '/', '\\');
            createDirectory(folderPath);

            string download_svnfile_cmd =
                    "svn export --force " + svnExportPath + "@" + to_string(version) + " " + exportPath;
            string downloadStatuResult = cmdProcess(download_svnfile_cmd.c_str());
        }
    }
}

