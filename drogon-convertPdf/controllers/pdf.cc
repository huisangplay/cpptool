#include "pdf.h"
#include "../constants/ViewConstant.h"
#include <drogon/MultiPart.h>
#include <rpc.h>
#include<string>
#include "../utils/DocToUtil.h"
#include "../constants/MessageConstant.h"
#include "../constants/FileExtensionConstant.h"
#include "../constants/PdfConverConstant.h"
#include <filesystem>

void pdf::index(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    HttpResponsePtr resp = HttpResponse::newHttpViewResponse(view::INDEX_PAGE);
    callback(resp);
}

void pdf::convertPdf(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    MultiPartParser fileUpload;
    drogon::HttpViewData data;
    if (fileUpload.parse(req) != 0 || fileUpload.getFiles().size() != 1) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("Must only be one file");
        resp->setStatusCode(k403Forbidden);
        callback(resp);
        return;
    }
    auto &file = fileUpload.getFiles()[0];
    UUID uuid;
    UuidCreate(&uuid); // 生成随机UUID
    RPC_CSTR uuidStr;
    UuidToStringA(&uuid, &uuidStr); // 将UUID转换为字符串

    std::string folderPath = reinterpret_cast<const char *const>(uuidStr);
    file.save(folderPath);
    folderPath = "uploads\\" + folderPath;
    RpcStringFreeA(&uuidStr); // 释放字符串内存

    std::string uploadFilePath = folderPath + "\\" + file.getFileName();
    std::string uploadFileSavePath = folderPath + "\\" + file.getFileName();
    std::string uploadFileName = file.getFileName();
    std::string destFilePath;
    std::string destFileName = uploadFileName;
    std::string::size_type pos = uploadFileName.rfind('.'); // 查找最后一个点号的位置
    destFileName.replace(pos, std::string::npos, ".pdf"); // 替换扩展名
    destFilePath = folderPath + "\\" + destFileName;



    string_view extension = file.getFileExtension();
    docTo::convertPdf(uploadFilePath.c_str(), destFilePath.c_str(), file.getFileExtension().data());
    if (extension == fileExtension::FILE_EXTENSION_DOC ||
        extension == fileExtension::FILE_EXTENSION_DOCX ||
        extension == fileExtension::FILE_EXTENSION_WPS ||
        extension == fileExtension::FILE_EXTENSION_RFT) {
        docTo::convertDocToPdf(uploadFilePath.c_str(), destFilePath.c_str());
    } else if (extension == fileExtension::FILE_EXTENSION_PPT ||
               extension == fileExtension::FILE_EXTENSION_PPTX) {
        docTo::convertPPTToPdf(uploadFilePath.c_str(), destFilePath.c_str());
    } else if (extension == fileExtension::FILE_EXTENSION_XLS ||
               extension == fileExtension::FILE_EXTENSION_XLSX) {
        docTo::convertExcelToPdf(uploadFilePath.c_str(), destFilePath.c_str());
    } else {
        LOG_WARN << uploadFileName << " is not support...";
    }

    if (std::filesystem::exists(destFilePath)) {
        std::filesystem::path destFile(destFilePath);
        // 设置响应头
        auto resp = HttpResponse::newFileResponse(destFilePath, destFileName, CT_APPLICATION_OCTET_STREAM);

        // 发送响应头
        callback(resp);
    } else {
        data.insert(message::MESSAGE_WARNING_DEFINITION, pdfConvert::CONVERT_PDF_FAILED);
        HttpResponsePtr resp = HttpResponse::newHttpViewResponse(view::INDEX_PAGE, data);
        callback(resp);
    }
    std::filesystem::remove_all(folderPath);
}