#include "UserController.h"
#include "../models/UsUser.h"
#include "../constants/UserConstant.h"
#include "../constants/MessageConstant.h"
#include "../constants/ViewConstant.h"
// Add definition of your processing function here
void UserController::loginAuth(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    std::string resultPage;
    auto params = req->getParameters();

    std::string username = params.at("username");
    std::string password = params.at("password");

    // 这里验证用户名和密码,如果成功,设置 Session
    auto clientPtr = drogon::app().getDbClient("sqlite3");
    drogon::HttpViewData data;
    drogon::orm::Mapper<drogon_model::sqlite3::UsUser> mp(clientPtr);
    auto users=mp.findBy((drogon::orm::Criteria(drogon_model::sqlite3::UsUser::Cols::_user_name,drogon::orm::CompareOperator::EQ,username))
            &&(drogon::orm::Criteria(drogon_model::sqlite3::UsUser::Cols::_user_password,drogon::orm::CompareOperator::EQ,password)));
    if(users.size()>0){
        data.insert(message::MESSAGE_INFO_DEFINITION, user::LOGIN_SUCCESS_MESSAGE);
        req->getSession()->insert("username",username);
        resultPage=view::INDEX_PAGE;
    } else{
        data.insert(message::MESSAGE_WARNING_DEFINITION, user::LOGIN_FAILED_MESSAGE);
        resultPage=view::LOGIN_PAGE;
    }
    // 返回登录成功的响应
    HttpResponsePtr resp = HttpResponse::newHttpViewResponse(resultPage,data);
    callback(resp);
}

void UserController::userLoginPage(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto resp = drogon::HttpResponse::newHttpViewResponse(view::LOGIN_PAGE);
    callback(resp);
}

void UserController::userLogOut(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback){
    drogon::HttpViewData data;
    data.insert(message::MESSAGE_WARNING_DEFINITION, user::LOGOUT_SUCCESS_MESSAGE);
    HttpResponsePtr resp = HttpResponse::newHttpViewResponse(view::LOGIN_PAGE,data);
    callback(resp);
}