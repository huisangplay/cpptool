#pragma once

#include <drogon/HttpController.h>
#include "../constants/PdfConverConstant.h"
using namespace drogon;

class pdf : public drogon::HttpController<pdf> {
public:
    METHOD_LIST_BEGIN

        METHOD_ADD(pdf::index, "/index", Get);
        METHOD_ADD(pdf::convertPdf, "/convertPdf", Post);
        METHOD_ADD(pdf::convertPdf, "/upload", Post);

    METHOD_LIST_END

    static void index(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    static void convertPdf(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};

class api : public drogon::HttpController<api> {
public:
    METHOD_LIST_BEGIN

        METHOD_ADD(api::serviceMonitor, "/serviceMonitor", Get);

    METHOD_LIST_END

    static void serviceMonitor(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody(pdfConvertConstant::CONVERT_SERVICE_MONITOR);
        callback(resp);
    }

};
