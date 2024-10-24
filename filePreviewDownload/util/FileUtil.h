//
// Created by ZHOU on 24-10-25.
//

#ifndef FILEUTIL_H
#define FILEUTIL_H
#include<filesystem>
#include <fstream>
std::string readFile(std::filesystem::path &path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}


#endif //FILEUTIL_H
