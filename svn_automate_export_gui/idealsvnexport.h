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
#include "utils/stringutil.h"
#include "utils/windowsutil.h"
using namespace std;
void getIDEALSvnInfoAndDownloadFilesFromCmd(int version,string submit_path);
void ideal_svn_export(vector<int>& svn_nums,string submit_path,vector<string>& exportfilelist);
