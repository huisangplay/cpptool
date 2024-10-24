//
// Created by ZHOU on 24-10-25.
//

#ifndef COMPRESSUTIL_H
#define COMPRESSUTIL_H


#include<filesystem>
#include<iostream>
#include<fstream>
#include "miniz.h"
void zip_directory(const std::string& zip_filename, const std::string& directory) {
    mz_zip_archive zip_archive;
    memset(&zip_archive, 0, sizeof(zip_archive));

    // 创建 ZIP 文件
    if (!mz_zip_writer_init_file(&zip_archive, zip_filename.c_str(), 0)) {
        std::cerr << "Failed to initialize zip file: " << zip_filename << std::endl;
        return;
    }

    // 遍历目录并添加文件到 ZIP
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            const auto& path = entry.path();
            std::string relative_path = std::filesystem::relative(path, directory).string();

            // 添加文件到 ZIP
            if (!mz_zip_writer_add_file(&zip_archive, relative_path.c_str(), path.string().c_str(), nullptr, 0, MZ_BEST_COMPRESSION)) {
                std::cerr << "Failed to add file: " << path << std::endl;
            }
        }
    }

    // 完成 ZIP 文件
    mz_zip_writer_finalize_archive(&zip_archive);
    mz_zip_writer_end(&zip_archive);
}

#endif //COMPRESSUTIL_H
