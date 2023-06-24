#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class UserController : public drogon::HttpController<UserController> {
public:
    METHOD_LIST_BEGIN

        METHOD_ADD(UserController::loginAuth, "/loginAuth", Post);
        METHOD_ADD(UserController::userLoginPage, "/loginPage", Get);
        METHOD_ADD(UserController::userLogOut, "/logOut", Get);

    METHOD_LIST_END

    void loginAuth(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    void userLoginPage(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    void userLogOut(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

};
