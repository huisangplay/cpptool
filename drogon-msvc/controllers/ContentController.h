#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class ContentController : public drogon::HttpController<ContentController> {
public:
    METHOD_LIST_BEGIN
        // use METHOD_ADD to add your custom processing function here;
        METHOD_ADD(ContentController::index, "/index", Get);
        METHOD_ADD(ContentController::customerList, "/consumer/list", Get);

    METHOD_LIST_END

    // your declaration of processing function maybe like this:
    void customerList(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    void index(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
};
