/**
 *
 *  LoginFilter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
#include "drogon/HttpAppFramework.h"

using namespace drogon;


class LoginFilter : public HttpFilter<LoginFilter>
{

  public:
    LoginFilter() {}
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;

    static constexpr bool isAutoCreation = false;
};
