#include <iostream>
#include<string>
#include<vector>
#include <filesystem>
#include<fstream>
namespace fs = std::filesystem;
using namespace std;
void getFiles(string path, vector<string>& files);
bool find_substring_from_text(string file_path, string substring);
int main()
{
	vector<string> files;
	string value;
	cout << "请输入需要查询的字符串..." << endl;
	cin >> value;
	//获取该路径下的所有文件
	getFiles(".", files);

	for (int i = 0; i < files.size(); i++)
	{
		bool flag = find_substring_from_text(files[i], value);
		if (flag) {
			cout << "substring is present at file " << files[i] << ",open this file with vscode..." << endl;
			system(string("code " + files[i]).c_str());
			cout << "按回车继续搜索" << endl;
			system("pause");
		}
	}
	system("pause");
	return 0;
}

void getFiles(string path, vector<string>& files)
{
	for (const auto& entry : fs::directory_iterator(path))
		files.push_back(entry.path().string());
}

bool find_substring_from_text(string file_path, string substring) {
	ifstream file_text(file_path);  // creating file_text object of ifstream type.
	string linestr;
	bool ans = false;
	if (file_text.is_open())       //is_open open the text file.
	{
		while (getline(file_text, linestr))
		{
			if (linestr.find(substring, 0) != string::npos) {
				ans = true;
				break;
			}
		}
		file_text.close(); //to close text file.
	}
	else
		cout << "Unable to open file:" << file_path << endl;;
	if (!ans)   // if subtring not present.
		cout << "subtring not present is present" << file_path << endl;
	return ans;
}