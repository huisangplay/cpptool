#include "idealsvnexport.h"
void ideal_svn_export(vector<int>& svn_nums,string submit_path,vector<string>& exportfilelist){
    setlocale(LC_ALL, "zh_CN");

    for (int svn_num: svn_nums) {
        cout<<svn_num<<"123"<<endl;
        getIDEALSvnInfoAndDownloadFilesFromCmd(svn_num,submit_path);
    }

    vector<string> filelist;

    getAllFiles(submit_path+"\\��Ŀ����", filelist);

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
    cout << "svn����λ�ã�"+submit_path << endl;
    cout << "svn�����ļ��б�λ�ã�"+submit_path+"\\ideal_export_file_list.txt" << endl;
    cout<<"svn�ļ��������...."<<endl;
}

void getIDEALSvnInfoAndDownloadFilesFromCmd(int version,string submit_path) {
    cout << "��ʼ����svn:" << version << endl;
    string showdiffcmd = "svn diff -r " + to_string(version - 1) + ":" + to_string(version) +
                         " --summarize http://vcs.comac.intra/svn/sadri/��Ŀ����";

    string changeListResult = cmdProcess(showdiffcmd.c_str());

    vector<string> changeList = split(changeListResult, '\n');
    for (int i = 0; i < changeList.size(); ++i) {

        string change = changeList.at(i);
        vector<string> changeInfoList = split(remove_surplus_spaces(change), ' ');

        string action = changeInfoList.at(0);
        if(action=="") {
            continue;
        }
        string path = "/��Ŀ����" + changeInfoList.at(1).substr(69);
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
            cout << "ɾ��·��:" << exportPath << endl;
        } else {
            //����ǰ�Ƚ����ļ��У����򵼳�ʧ��
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

