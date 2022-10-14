//
// Created by 500958 on 2022/10/9.
//

#include "search_excel.h"

bool search_excel_xls(std::string filepath, std::string findstr) {
    Book *book = xlCreateBook();
    setLibxlKey(book);
    return search_excel(filepath, findstr, book);

}

bool search_excel_xlsx(std::string filepath, std::string findstr) {
    Book *book = xlCreateXMLBook();
    setLibxlKey(book);
    return search_excel(filepath, findstr, book);
}

bool search_excel(std::string filepath, const std::string findstr, Book *book) {
    if (book->load(filepath.c_str())) {
        for (int i = 0; i < book->sheetCount(); ++i) {
            Sheet *sheet = book->getSheet(i);
            if (!sheet)
                continue;
            int rowNum = sheet->lastRow();
            int colNum = sheet->lastCol();
            for (int j = 0; j < rowNum; ++j) {
                for (int k = 0; k < colNum; ++k) {
                    const char *cellstr = nullptr;
                    CellType ct = sheet->cellType(j, k);
                    switch (ct) {
                        case CELLTYPE_NUMBER:
                            cellstr = std::to_string(sheet->readNum(j, k)).c_str();
                            break;
                        case CELLTYPE_STRING:
                            cellstr = sheet->readStr(j, k);
                            break;
                        case CELLTYPE_BOOLEAN:
                            cellstr = sheet->readBool(j, k) ? "true" : "false";
                            break;
                    }
                    if (cellstr == nullptr) continue;
                    std::string cellstring = cellstr;
                    if (cellstring.find(findstr) != std::string::npos) {
                        book->release();
                        return true;
                    }
                }
            }
        }
        book->release();
    }
    return false;
}

void setLibxlKey(Book *book) {
    book->setKey("zhouhui", "windows-2b212a0206cfe00365b6686dafpar7g1");
}