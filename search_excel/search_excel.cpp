#include <iostream>
#include "libxl.h"
#include <vector>
#include<map>
#include<filesystem>
#include<string>
using namespace libxl;
using namespace std;
namespace fs = std::filesystem;
void getFiles(const wstring& path, map<wstring, vector<wstring>>& map);
void search_excel(wstring file, const wchar_t* findstr, Book* book);
void search_excel_xls(vector<wstring> files, const wchar_t* findstr);
void search_excel_xlsx(vector<wstring> files, const wchar_t* findstr);
void setLibxlKey(Book* book);
int main() {
	//设置语言区域为中国，wcout可显示中文
	wcout.imbue(locale("chs"));

	wstring path = L"D:\\test";
	const wchar_t* findstr = L"500";
	map<wstring, vector<wstring>> map;
	map.insert(pair<wstring, vector<wstring>>(L".xls", vector<wstring>()));
	map.insert(pair<wstring, vector<wstring>>(L".xlsx", vector<wstring>()));
	getFiles(path, map);

	auto iter = map.begin();
	while (iter != map.end()) {
		wstring filetype = iter->first;
		vector<wstring> files = iter->second;
		if (filetype == L".xls" && files.size() != 0) {
			search_excel_xls(files, findstr);
		}
		else if (filetype == L".xlsx" && files.size() != 0) {
			search_excel_xlsx(files, findstr);
		}
		iter++;
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

void search_excel_xls(vector<wstring> files, const wchar_t* findstr) {
	for (wstring file : files) {
		Book* book = xlCreateBook();
		setLibxlKey(book);
		search_excel(file, findstr, book);
	}
}

void search_excel_xlsx(vector<wstring> files, const wchar_t* findstr) {
	for (wstring file : files) {
		Book* book = xlCreateXMLBook();
		setLibxlKey(book);
		search_excel(file, findstr, book);
	}
}

void search_excel(wstring file, const wchar_t* findstr, Book* book) {
	if (book->load(file.c_str())) {
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
						wcout << L"this file have:" << file << endl;
						return;
					}
				}
			}
		}
		book->release();
	}
}

void setLibxlKey(Book* book) {
	book->setKey(L"zhouhui", L"windows-2b212a0206cfe00365b6686dafpar7g1");
}