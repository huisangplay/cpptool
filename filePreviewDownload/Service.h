//
// Created by ZHOU on 24-10-25.
//

#ifndef SERVICE_H
#define SERVICE_H
#include <fstream>
#include<filesystem>
#include<string>
#include"util/httplib.h"
#include"uploadHtml.h"
#include"util/FileUtil.h"
#include"util/TimeUtil.h"
#include"util/CompressUtil.h"
using namespace httplib;

inline void showUploadPage(const Request & /*req*/, Response &res) {
    res.set_header("Access-Control-Allow-Origin","*");
    res.set_content(uploadHtml, "text/html");
}

inline void uploadFile(const Request &req, Response &res) {
    auto uploadFile = req.get_file_value("uploadFile");
    auto fileDescribe = req.get_file_value("fileDescribe").content;

    std::cout << "upload file length: " << uploadFile.content.length() << std::endl
            << "upload file name: " << uploadFile.filename << std::endl;

    std::string folderPath = "uploads\\" + fileDescribe; {
        std::ofstream ofs(folderPath, std::ios::binary);
        ofs << uploadFile.content;
        if (!ofs.good()) {
            ofs.clear();
        }
        ofs.close();
    }
    res.set_header("Access-Control-Allow-Origin","*");
    res.set_redirect("/userGuideFile/uploadFile");
}


inline void showFileList(const Request &req, Response &res) {
    std::string folder = req.get_param_value("folder");
    std::string fileListHtml;
    std::vector<std::filesystem::path> files;
    try {
        std::string folerPath = "./uploads/" + folder;
        if (std::filesystem::exists(folerPath) && std::filesystem::is_directory(folerPath)) {
            for (const auto &entry: std::filesystem::directory_iterator(folerPath)) {
                if (std::filesystem::is_regular_file(entry.path())) {
                    files.push_back(entry.path());
                }
            }
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    std::string fileHyperLinkListStr = R"(<meta charset="UTF-8"><ul>)";
    for (const auto &file: files) {
        fileHyperLinkListStr.append(
            "<li><a href='/userGuideFile/preview?folder=" + folder + "&filename=" + file.filename().string() +
            "' target='_blank'>");
        fileHyperLinkListStr.append(file.filename().string());
        fileHyperLinkListStr.append("</a></li>");
    }
    fileHyperLinkListStr.append("</ul>");
    std::cout << fileHyperLinkListStr << std::endl;
    res.set_header("Access-Control-Allow-Origin","*");
    res.set_content(fileHyperLinkListStr.c_str(), "text/html");
}

inline void filePreview(const Request &req, Response &res) {
    res.set_header("Access-Control-Allow-Origin","*");
    std::string filename = req.get_param_value("filename");
    std::string folder = req.get_param_value("folder");
    std::filesystem::path filePath = "./uploads/" + folder + "/" + filename;
    try {
        std::filesystem::path extension;
        if (exists(filePath) && is_regular_file(filePath)) {
            // 获取文件扩展名
            extension = filePath.extension();
        }
        if (extension == ".mp4") {
            std::string video_content = readFile(filePath);
            res.set_content(video_content, "video/mp4");
        } else if (extension == ".pdf") {
            std::string video_content = readFile(filePath);
            res.set_content(video_content, "application/pdf");
        }
    } catch (const std::exception &e) {
        res.status = 500;
        res.set_content("Internal Server Error", "text/plain");
    }
}

void downloadAllFiles(const httplib::Request &req, httplib::Response &res) {
    res.set_header("Access-Control-Allow-Origin","*");
    std::filesystem::path zip_file_path = "./download/" + get_current_time() + ".zip";
    zip_directory(zip_file_path.string(), "./uploads");
    try {
        // 读取 ZIP 文件
        std::string zip_content = readFile(zip_file_path);
        // 设置响应头
        res.set_content(zip_content,  "application/zip");
        res.set_header("Content-Disposition", "attachment; filename=XBOM_HELPER_ALL_FILES.zip");
    } catch (const std::exception &e) {
        res.status = 500; // 内部服务器错误
        res.set_content(e.what(), "text/plain");
    }
    if (exists(zip_file_path)) {
        // 删除文件
        remove(zip_file_path);
    }
}

#endif //SERVICE_H
