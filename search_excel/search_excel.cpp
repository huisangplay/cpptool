#pragma warning(disable:4996)
#include <iostream>
#include "libxl.h"
#include <vector>
#include<map>
#include<filesystem>
#include<string>
#include<fstream>
#include<codecvt>
using namespace libxl;
using namespace std;
namespace fs = std::filesystem;
void getFiles(const wstring& path, map<wstring, vector<wstring>>& map);
void search_excel(wstring file, wstring findstr, Book* book, vector<wstring>& output_filepaths);
void search_excel_xls(vector<wstring> files, wstring findstr, vector<wstring>& output_filepaths);
void search_excel_xlsx(vector<wstring> files, wstring findstr, vector<wstring>& output_filepaths);
void search_text(wstring file_path, wstring findstr, vector<wstring>& output_filepaths);
void search_xml(wstring file_path, wstring findstr, vector<wstring>& output_filepaths);
void setLibxlKey(Book* book);
int main() {
	//设置语言区域为中国，wcout可显示中文
	wcout.imbue(locale("chs"));
	wcin.imbue(locale("chs"));
	wstring path;
	wstring findstr;
	map<wstring, vector<wstring>> map;
	map.insert(pair<wstring, vector<wstring>>(L".xls", vector<wstring>()));
	map.insert(pair<wstring, vector<wstring>>(L".xlsx", vector<wstring>()));
	map.insert(pair<wstring, vector<wstring>>(L".xml", vector<wstring>()));
	map.insert(pair<wstring, vector<wstring>>(L".ini", vector<wstring>()));
	map.insert(pair<wstring, vector<wstring>>(L".csv", vector<wstring>()));
	
	vector<wstring> output_filepaths;

	auto iter = map.begin();
	wcout << L"当前搜索程序支持文件类型为:" << endl;
	while (iter != map.end()) {
		wcout << iter->first << endl;
		iter++;
	}
	wcout << L"如需添加文件类型，请联系作者..." << endl;
	wcout << L"请输入需要搜索的字符串:" << endl;
	getline(wcin,findstr);
	wcout << L"请输入需要搜索的文件夹位置:" << endl;
	wcin >> path;
	wcout << L"开始遍历文件夹..." << endl;

	getFiles(path, map);

	wcout << L"开始搜索字符串..." << endl;
	iter = map.begin();
	while (iter != map.end()) {
		wstring filetype = iter->first;
		vector<wstring> filepaths = iter->second;
		if (filetype == L".xls" && filepaths.size() != 0) {
			search_excel_xls(filepaths, findstr,output_filepaths);
		}
		else if (filetype == L".xlsx" && filepaths.size() != 0) {
			search_excel_xlsx(filepaths, findstr, output_filepaths);
		}
		else if ((filetype == L".ini" || filetype == L".csv") && filepaths.size() != 0) {
			for (auto filepath : filepaths) {
				search_text(filepath, findstr, output_filepaths);
			}
		}
		else if (filetype == L".xml"&&filepaths.size() != 0) {
			for (auto filepath : filepaths) {
				search_xml(filepath, findstr, output_filepaths);
			}
		}
		iter++;
	}
	if (output_filepaths.size() == 0) {
		wcout << L"未搜索到指定字符串..." << endl;
	}
	else {
		wcout << L"指定字符串位于以下文件中:" << endl;
		for (auto filepath : output_filepaths) {
			wcout << filepath << endl;
		}
	}
	system("pause");
	return 0;
}

void getFiles(const wstring& path, map<wstring, vector<wstring>>& map) {
	for (auto& file : fs::recursive_directory_iterator(path))
	{
		wstring tail = file.path().extension().wstring();
		if (!tail.empty() && map.find(tail) != map.end()) {
			(&(map.find(tail)->second))->push_back(file.path().wstring());
		}
	}
}

void search_excel_xls(vector<wstring> filepaths, wstring findstr, vector<wstring>& output_filepaths) {
	for (wstring filepath : filepaths) {
		Book* book = xlCreateBook();
		setLibxlKey(book);
		search_excel(filepath, findstr, book, output_filepaths);
	}
}

void search_excel_xlsx(vector<wstring> filepaths, wstring findstr, vector<wstring>& output_filepaths) {
	for (wstring filepath : filepaths) {
		Book* book = xlCreateXMLBook();
		setLibxlKey(book);
		search_excel(filepath, findstr, book, output_filepaths);
	}
}

void search_excel(wstring filepath, const wstring findstr, Book* book, vector<wstring>& output_filepaths) {
	if (book->load(filepath.c_str())) {
		for (int i = 0; i < book->sheetCount(); ++i) {
			Sheet* sheet = book->getSheet(i);
			if (!sheet)
				continue;
			int rowNum = sheet->lastRow();
			int colNum = sheet->lastCol();
			for (int j = 0; j < rowNum; ++j) {
				for (int k = 0; k < colNum; ++k) {
					const wchar_t* cellstr = nullptr;
					CellType ct = sheet->cellType(j, k);
					switch (ct) {
					case CELLTYPE_NUMBER:
						cellstr = to_wstring(sheet->readNum(j, k)).c_str();
						break;
					case CELLTYPE_STRING:
						cellstr = sheet->readStr(j, k);
						break;
					case CELLTYPE_BOOLEAN:
						cellstr = sheet->readBool(j, k) ? L"true" : L"false";
						break;
					}
					if (cellstr == nullptr) continue;
					if (wstring(cellstr).find(findstr) != string::npos) {
						output_filepaths.push_back(filepath);
						return;
					}
				}
			}
		}
		book->release();
	}
}
void search_text(wstring filepath, wstring findstr, vector<wstring>& output_filepaths) {
	wifstream file_text(filepath);  
	//file_text.imbue(locale(locale::empty(),new codecvt_utf8<wchar_t>));
	file_text.imbue(locale("chs"));
	wstring linestr;
	if (file_text.is_open())       
	{
		while (getline(file_text, linestr))
		{
			wcout << linestr <<endl;
			const wstring temp = linestr;
			if (linestr.find(findstr, 0) != wstring::npos) {
				output_filepaths.push_back(filepath);
				break;
			}
		}
		file_text.close();
	}
	else
		wcout << L"Unable to open file:" << filepath << endl;
}
void setLibxlKey(Book* book) {
	book->setKey(L"zhouhui", L"windows-2b212a0206cfe00365b6686dafpar7g1");
}
void search_xml(wstring filepath, wstring findstr, vector<wstring>& output_filepaths) {
	wifstream wif(filepath, ios::binary);
	wif.imbue(locale(locale::empty(),new codecvt_utf8<wchar_t>));
	if (wif.is_open())
	{
		std::wstring linestr;
		while (getline(wif, linestr))
		{
			
			if (linestr.find(findstr, 0) != wstring::npos) {
				output_filepaths.push_back(filepath);
				break;
			}
		}
		wif.close();
	}
	else
		wcout << L"Unable to open file:" << filepath << endl;
}