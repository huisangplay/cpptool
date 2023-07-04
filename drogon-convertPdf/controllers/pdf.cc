#include "pdf.h"
#include "../constants/ViewConstant.h"
#include <drogon/MultiPart.h>
#include <rpc.h>
#include<string>
#include "../utils/DocToUtil.h"
#include "../constants/FileConstant.h"
#include <filesystem>

void pdf::index(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    HttpResponsePtr resp = HttpResponse::newHttpViewResponse(view::INDEX_PAGE);
    callback(resp);
}

void pdf::convertPdf(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    MultiPartParser fileUpload;
    if (fileUpload.parse(req) != 0 || fileUpload.getFiles().size() != 1) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody(pdfConvertConstant::CONVERT_UPLOAD_FAILED);
        resp->setStatusCode(k403Forbidden);
        callback(resp);
        return;
    }

    auto &file = fileUpload.getFiles()[0];
    UUID uuid;
    UuidCreate(&uuid);
    RPC_CSTR uuidStr;
    UuidToStringA(&uuid, &uuidStr);
    std::string folderPath = reinterpret_cast<const char *const>(uuidStr);
    file.save(folderPath);
    RpcStringFreeA(&uuidStr);

    folderPath = fileConstant::FILE_UPLOAD_FOLDER + fileConstant::FILE_PATH_SEPARATOR + folderPath;

    string_view extension = file.getFileExtension();
    std::string uploadFilePath = folderPath + fileConstant::FILE_PATH_SEPARATOR + file.getFileName();
    std::string uploadFileSavePath = folderPath + fileConstant::FILE_PATH_SEPARATOR + file.getFileName();
    std::string uploadFileName = file.getFileName();
    std::string destFilePath;
    std::string destFileName = uploadFileName;
    std::string::size_type pos = uploadFileName.rfind(fileConstant::FILE_EXTENSION_SEPARATOR);
    destFileName.replace(pos+1, std::string::npos, fileConstant::FILE_EXTENSION_PDF);
    destFilePath = folderPath + fileConstant::FILE_PATH_SEPARATOR + destFileName;

    docTo::convertPdf(uploadFilePath.c_str(), destFilePath.c_str(), file.getFileExtension().data());
    if (extension == fileConstant::FILE_EXTENSION_DOC ||
        extension == fileConstant::FILE_EXTENSION_DOCX ||
        extension == fileConstant::FILE_EXTENSION_WPS ||
        extension == fileConstant::FILE_EXTENSION_RFT) {
        docTo::convertDocToPdf(uploadFilePath.c_str(), destFilePath.c_str());
    } else if (extension == fileConstant::FILE_EXTENSION_PPT ||
               extension == fileConstant::FILE_EXTENSION_PPTX) {
        docTo::convertPPTToPdf(uploadFilePath.c_str(), destFilePath.c_str());
    } else if (extension == fileConstant::FILE_EXTENSION_XLS ||
               extension == fileConstant::FILE_EXTENSION_XLSX ||
               extension == fileConstant::FILE_EXTENSION_CSV) {
        docTo::convertExcelToPdf(uploadFilePath.c_str(), destFilePath.c_str());
    }

    if (std::filesystem::exists(destFilePath)) {
        auto resp = HttpResponse::newFileResponse(destFilePath, destFileName, CT_APPLICATION_OCTET_STREAM);
        callback(resp);
    } else {
        HttpResponsePtr resp = HttpResponse::newHttpViewResponse(view::INDEX_PAGE);
        resp->setBody(pdfConvertConstant::CONVERT_PDF_FAILED);
        resp->setStatusCode(k403Forbidden);
        LOG_WARN << uploadFileName << pdfConvertConstant::CONVERT_PDF_FAILED;
        callback(resp);
    }
    std::filesystem::remove_all(folderPath);
}