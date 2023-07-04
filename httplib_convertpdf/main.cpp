#include <fstream>
#include "httplib.h"
#include <iostream>
#include <filesystem>
#include "DocToUtil.h"
#include "FileConstant.h"
#include "sqlite3.h"
#include "convert_bytes.h"
#include "StringUtil.h"
using namespace httplib;
using namespace std;
const char dbFile[] = "usersupport.db";
const char *uploadHtml = R"(
<!doctype html>
<html lang="zh-CN" data-bs-theme="auto">
<head>
<meta charset="UTF-8">
	<title>pdf自动转换</title>
	<style>
    		body {
              margin: 20px 60px;
            }

            .drop-container {
              position: relative;
              display: flex;
              gap: 10px;
              flex-direction: column;
              justify-content: center;
              align-items: center;
              height: 200px;
              padding: 20px;
              border-radius: 10px;
              border: 2px dashed #555;
              color: #444;
              cursor: pointer;
              transition: background .2s ease-in-out, border .2s ease-in-out;
            }

            .drop-container:hover {
              background: #eee;
              border-color: #111;
            }

            .drop-container:hover .drop-title {
              color: #222;
            }

            .drop-title {
              color: #444;
              font-size: 20px;
              font-weight: bold;
              text-align: center;
              transition: color .2s ease-in-out;
            }

            input[type=file] {
              width: 350px;
              max-width: 100%;
              color: #444;
              padding: 5px;
              background: #fff;
              border-radius: 10px;
              border: 1px solid #555;
            }

            input[type=file]::file-selector-button {
              margin-right: 20px;
              border: none;
              background: #084cdf;
              padding: 10px 20px;
              border-radius: 10px;
              color: #fff;
              cursor: pointer;
              transition: background .2s ease-in-out;
            }

            input[type=file]::file-selector-button:hover {
              background: #0d45a5;
            }

            button[type=submit]{
                font-size: 20px;
                width:100%;
                margin-top:5px;
                text-align: center;
                height=70px;
                border: 1px solid;
                border-radius: 5px;
                cursor: pointer;
                transition: background .2s ease-in-out;
            }
            button[type=submit]:hover{
                background: #ddd;
                border-color: #222;
            }
    	</style>
</head>
<div class="container">
    <form action="/pdf/upload" method="post" enctype="multipart/form-data" class="form">
      <label for="file" class="drop-container">
        <span class="drop-title">自动转换pdf，支持非加密的doc、docx、xls、xlsx、csv、ppt、pptx、wps、rtf、vsd、vsdx格式的文档转换</span>
        <span class="drop-title">将文件拖入或者上传</span>
        <input type="file" id="file" name="uploadFile" required>
      </label>
      <button type="submit">转换</button>
    </form>
</div>
)";

int main() {

    {
        // 打开文件并读取数据
        std::ifstream convertFile("convert.exe", std::ios::binary);
        if (!convertFile.is_open()) {
            // 将数据写入文件
            std::cout << "can not find convert.exe file , start to create convert.exe file..." << endl;
            std::ofstream ofs("convert.exe", std::ios::binary);
            if (ofs.is_open()) {
                ofs.write(reinterpret_cast<const char *>(convert_exe), sizeof(convert_exe));
                ofs.close();
                std::cout << "create susscess!" << endl;
            } else {
                std::cerr << "can not create convert.exe file... service aborted!\n";
                return 1;
            }
        }

        sqlite3 *db;
        if (sqlite3_open(dbFile, &db) != SQLITE_OK) {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS [pdf_convert_record](\n"
                         "  [source_ip] TEXT, \n"
                         "  [convert_time] DATETIME, \n"
                         "  [file_name] TEXT, \n"
                         "  [convert_state] BOOLEAN);", 0, 0, nullptr);
        sqlite3_close(db);
    }

    Server svr;

    svr.Get("/pdf/uploadFile", [](const Request & /*req*/, Response &res) {
        res.set_content(uploadHtml, "text/html");
    });

    svr.Get("/api/serviceMonitor", [](const Request & /*req*/, Response &res) {
        res.set_content("pdfService is running...", "text/plain");
    });

    svr.Post("/pdf/upload", [](const Request &req, Response &res) {
        auto uploadFile = req.get_file_value("uploadFile");

        cout << "upload file length: " << uploadFile.content.length() << endl
             << "upload file name: " << uploadFile.filename << endl;

        UUID uuid;
        UuidCreate(&uuid);
        RPC_CSTR uuidStr;
        UuidToStringA(&uuid, &uuidStr);
        std::string folderPath = reinterpret_cast<const char *const>(uuidStr);
        folderPath = "uploads\\" + folderPath;
        RpcStringFreeA(&uuidStr);

        std::filesystem::path uploadFilePath(stringutil::UTF8_2_GBK( folderPath + "\\" + uploadFile.filename));
        std::filesystem::path destFilePath(uploadFilePath);
        destFilePath.replace_extension(".pdf");
        std::string extension = uploadFilePath.extension().string();

        {
            filesystem::create_directories(uploadFilePath.parent_path());
            ofstream ofs(uploadFilePath, ios::binary);
            ofs << uploadFile.content;

            // 检查流状态并关闭文件流
            if (!ofs.good()) {
                ofs.clear(); // 清除流状态
            }
            ofs.close();
        }

        if (extension == fileConstant::FILE_EXTENSION_DOC ||
            extension == fileConstant::FILE_EXTENSION_DOCX ||
            extension == fileConstant::FILE_EXTENSION_WPS ||
            extension == fileConstant::FILE_EXTENSION_RFT) {
            docTo::convertDocToPdf(uploadFilePath.string().c_str(), destFilePath.string().c_str());
        } else if (extension == fileConstant::FILE_EXTENSION_PPT ||
                   extension == fileConstant::FILE_EXTENSION_PPTX) {
            docTo::convertPPTToPdf(uploadFilePath.string().c_str(), destFilePath.string().c_str());
        } else if (extension == fileConstant::FILE_EXTENSION_XLS ||
                   extension == fileConstant::FILE_EXTENSION_XLSX ||
                   extension == fileConstant::FILE_EXTENSION_CSV) {
            docTo::convertExcelToPdf(uploadFilePath.string().c_str(), destFilePath.string().c_str());
        } else if (extension == fileConstant::FILE_EXTENSION_VSD || extension == fileConstant::FILE_EXTENSION_VSDX) {
            docTo::convertVisioToPdf(uploadFilePath.string().c_str(), destFilePath.string().c_str());
        }


        bool convert_state = true;

        // 打开文件并读取数据
        std::ifstream destFile(destFilePath, std::ios::binary);
        if (!destFile.is_open()) {
            std::cout << uploadFile.filename << " pdf convert failed" << endl;
            convert_state = false;
            res.status = 404;
            res.set_content("pdf转换失败，请检查是否为加密文件或非支持文件", " text/plain; charset=utf-8");
        } else {
            std::vector<char> destFileData((std::istreambuf_iterator<char>(destFile)),
                                           std::istreambuf_iterator<char>());
            // 检查流状态并关闭文件流
            if (!destFile.good()) {
                destFile.clear(); // 清除流状态
            }
            destFile.close();
            std::cout << uploadFile.filename << " pdf convert success!" << endl;
            res.set_header("Content-Disposition", "attachment; filename=\"" + destFilePath.filename().string());
            res.set_header("Content-Type", "application/octet-stream;charset=UTF-8");
            res.set_header("Accept-Ranges", "bytes");
            res.set_content(destFileData.data(), destFileData.size(), "application/octet-stream;charset=UTF-8");
        }

        //std::filesystem::remove_all(folderPath);

        sqlite3 *db;
        if (sqlite3_open(dbFile, &db) != SQLITE_OK) {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
            return;
        }
        sqlite3_stmt *stmt;
        const char *sql = "INSERT INTO pdf_convert_record (source_ip, convert_time,file_name,convert_state) VALUES (?, datetime('now'), ?, ?)";
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot prepare SQL statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }
        sqlite3_bind_text(stmt, 1, req.remote_addr.c_str(), req.remote_addr.length(), nullptr);
        sqlite3_bind_text(stmt, 2, uploadFile.filename.c_str(), uploadFile.filename.length(), nullptr);
        sqlite3_bind_int(stmt, 3, convert_state);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            cout << "Cannot execute SQL statement: %s\n" << sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }
        sqlite3_reset(stmt);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    });

    std::cout
            << "The service is now running on the address 127.0.0.1:1994\n"
               "the pdf conversion interface is /pdf/upload\n"
               "web browser url is /pdf/uploadFile\n"
               "server monitor interface is /api/serviceMonitor\n";

    svr.listen("localhost", 1994);

}
