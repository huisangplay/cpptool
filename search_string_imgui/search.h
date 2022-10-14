#include <iostream>
#include <vector>
#include<map>
#include<string>
#include<filesystem>
#include"utils/search_excel.h"
#include"utils/search_text.h"
#include "utils/stringutil.h"
#include "utils/search_pdf.h"
#include "utils/search_doctotext.h"
using namespace std;
namespace fs = std::filesystem;
void getFiles(const std::string& path, std::map<std::string, std::vector<std::string>>& map);
void search(string findstr,std::map<string, vector<string>>& map,vector<string>& output_filepaths);
void search_strs_main(string path,string findstr,set<string> filetypes,vector<string>& output_filepaths);