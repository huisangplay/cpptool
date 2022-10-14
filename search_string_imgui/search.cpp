#include"search.h"

void search_strs_main(std::string path, std::string findstr, std::set<std::string> filetypes,
                      std::vector<std::string> &output_filepaths) {
    std::vector<std::string> findstrs = split(findstr, ';');
    map<std::string, std::vector<std::string>> map;
    for (auto filetype: filetypes) {
        map.insert(pair<string, vector<string>>(filetype, vector<string>()));
    }
    getFiles(path, map);
    for (string str: findstrs) {
        str = remove_surplus_spaces(str);
        if (str == "") continue;
        output_filepaths.push_back(UTF8_2_GBK("搜索字符:") + str);
        search(str, map, output_filepaths);
    }
}

void search(string findstr, std::map<string, vector<string>> &map, vector<string> &output_filepaths) {
    auto iter = map.begin();
    while (iter != map.end()) {
        string filetype = iter->first;
        vector<string> filepaths = iter->second;
        if (filetype == ".xls" && filepaths.size() != 0) {
            for (auto filepath: filepaths) {
                if (search_excel_xls(filepath, findstr)) output_filepaths.push_back(filepath);
            }
        } else if (filetype == ".xlsx" && filepaths.size() != 0) {
            for (auto filepath: filepaths) {
                if (search_excel_xlsx(filepath, findstr)) output_filepaths.push_back(filepath);
            }
        } else if (filetype == ".pdf" && filepaths.size() != 0) {
            for (auto filepath: filepaths) {
                if (search_pdf(filepath, GBK_2_UTF8(findstr))) output_filepaths.push_back(filepath);
            }
        }else if (filetype == ".doc"|| filetype == ".docx"||filetype == ".ppt"||filetype == ".pptx"&& filepaths.size() != 0) {
            for (auto filepath: filepaths) {
                if (search_doctotext(filepath, findstr)) output_filepaths.push_back(filepath);
            }
        }
        else if (filepaths.size() != 0) {
            for (auto filepath: filepaths) {
                if (search_text(filepath, findstr)) output_filepaths.push_back(filepath);
            }
        }
        iter++;
    }
}

void getFiles(const std::string &path, std::map<std::string, std::vector<std::string>> &map) {
    for (auto &file: fs::recursive_directory_iterator(path)) {
        std::string tail = file.path().extension().string();
        if (!tail.empty() && map.find(tail) != map.end()) {
            (&(map.find(tail)->second))->push_back(file.path().string());
        }
    }
}
