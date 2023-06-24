#include "ContentController.h"
#include "../constants/ViewConstant.h"
// Add definition of your processing function here
void ContentController::customerList(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback){

}

void ContentController::index(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback){
    HttpResponsePtr resp = HttpResponse::newHttpViewResponse(view::INDEX_PAGE);
    callback(resp);
}