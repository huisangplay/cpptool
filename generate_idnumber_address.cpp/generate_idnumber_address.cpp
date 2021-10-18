#include <iostream>
#include "libxl.h"
#include <vector>
#include<io.h>
#include<map>
#include <string> 
using namespace libxl;
using namespace std;

void setLibxlKey(Book* book) {
    book->setKey(L"zhouhui", L"windows-2b212a0206cfe00365b6686dafpar7g1");
}

vector<wstring> getIDNumberList() {
    vector<wstring> list;
    Book* book = xlCreateBook();
    setLibxlKey(book);
    if (book->load(L"IDNumver.xls")) {
        Sheet* sheet = book->getSheet(0);
        if (!sheet)
            return list;
        int rowNum = sheet->lastRow();
        for (int i = 1; i < rowNum; ++i) {
            wstring cellstr = L"";
            CellType ct = sheet->cellType(i, 3);
            switch (ct) {
            case CELLTYPE_EMPTY:
                continue;
            case CELLTYPE_NUMBER:
                cellstr = to_wstring((int)sheet->readNum(i,3));
                break;
            case CELLTYPE_STRING:
                cellstr = sheet->readStr(i, 3);
                break;
            case CELLTYPE_BOOLEAN:
                cellstr = sheet->readBool(i, 3) ? L"true" : L"false";
                break;
            default:
                cellstr = L"";
            }
            if (cellstr == L"") continue;
            list.push_back(cellstr);
        }
    }
    book->release();
    return list;
}

vector<wstring> addressList{ L"上海市市辖区黄浦区",
                           L"上海市市辖区南市区",
                           L"上海市市辖区卢湾区",
                           L"上海市市辖区徐汇区",
                           L"上海市市辖区长宁区",
                           L"上海市市辖区静安区",
                           L"上海市市辖区普陀区",
                           L"上海市市辖区闸北区",
                           L"上海市市辖区虹口区",
                           L"上海市市辖区杨浦区",
                           L"上海市市辖区吴凇区",
                           L"上海市市辖区闵行区",
                           L"上海市市辖区宝山区",
                           L"上海市市辖区嘉定区",
                           L"上海市市辖区浦东新区",
                           L"上海市市辖区金山区",
                           L"上海市市辖区松江区",
                           L"上海市市辖区青浦区",
                           L"上海市市辖区南汇区",
                           L"上海市市辖区奉贤区" };
wstring getAddress() {
    int size = addressList.size();
    return addressList[rand() % (size)];
}

int main() {
    Book* book = xlCreateBook();
    book->setLocale(LC_ALL);
    setLibxlKey(book);
    vector<wstring> list = getIDNumberList();
    int size = list.size();

    Sheet* sheet = book->addSheet(L"Sheet1");
    if (sheet) {
        for (int i = 0; i < 5000; ++i) {
            wstring idnumber = list[rand() % size];
            wstring address = getAddress();
            sheet->writeStr(i, 0, idnumber.c_str());
            sheet->writeStr(i, 1, address.c_str());
        }
    }
    book->save(L"身份证号和居住地.xls");
    book->release();

    return 0;
}