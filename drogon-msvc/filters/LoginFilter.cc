/**
 *
 *  LoginFilter.cc
 *
 */

#include "LoginFilter.h"
#include "drogon/HttpAppFramework.h"
#include "../constants/ViewConstant.h"
using namespace drogon;

void LoginFilter::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    auto session = req->session();
    if (session && !session->get<std::string>("username").empty())
    {
        fccb();
    }
    else
    {
        auto resp = drogon::HttpResponse::newHttpViewResponse(view::LOGIN_PAGE);
        fcb(resp);
    }
}