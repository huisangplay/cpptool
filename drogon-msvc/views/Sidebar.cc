//this file is generated by program(drogon_ctl) automatically,don't modify it!
#include "Sidebar.h"
#include <drogon/utils/OStringStream.h>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <list>
#include <deque>
#include <queue>
using namespace drogon;
std::string Sidebar::genText(const DrTemplateData& Sidebar_view_data)
{
	drogon::OStringStream Sidebar_tmp_stream;
	std::string layoutName{""};
	Sidebar_tmp_stream << "<div class=\"d-flex flex-column flex-shrink-0 p-3 text-bg-dark\" style=\"width: 280px;height:100vh;\">\n";
	Sidebar_tmp_stream << "    <a href=\"/\" class=\"d-flex align-items-center mb-3 mb-md-0 me-md-auto text-white text-decoration-none\">\n";
	Sidebar_tmp_stream << "      <span class=\"fs-4\">usersupport</span>\n";
	Sidebar_tmp_stream << "    </a>\n";
	Sidebar_tmp_stream << "    <hr>\n";
	Sidebar_tmp_stream << "    <ul class=\"nav nav-pills flex-column mb-auto\">\n";
	Sidebar_tmp_stream << "      <li class=\"nav-item\">\n";
	Sidebar_tmp_stream << "        <a href=\"/ContentController/index\" class=\"nav-link text-white\">\n";
	Sidebar_tmp_stream << "          主页\n";
	Sidebar_tmp_stream << "        </a>\n";
	Sidebar_tmp_stream << "      </li>\n";
	Sidebar_tmp_stream << "      <li>\n";
	Sidebar_tmp_stream << "        <a href=\"#\" class=\"nav-link text-white\">\n";
	Sidebar_tmp_stream << "          顾客\n";
	Sidebar_tmp_stream << "        </a>\n";
	Sidebar_tmp_stream << "      </li>\n";
	Sidebar_tmp_stream << "    </ul>\n";
	Sidebar_tmp_stream << "    <hr>\n";
	Sidebar_tmp_stream << "    <div class=\"dropdown\">\n";
	Sidebar_tmp_stream << "      <a href=\"#\" class=\"d-flex align-items-center text-white text-decoration-none dropdown-toggle\" data-bs-toggle=\"dropdown\" aria-expanded=\"false\">\n";
	Sidebar_tmp_stream << "        <strong>周辉</strong>\n";
	Sidebar_tmp_stream << "      </a>\n";
	Sidebar_tmp_stream << "      <ul class=\"dropdown-menu dropdown-menu-dark text-small shadow\">\n";
	Sidebar_tmp_stream << "        <li><a class=\"dropdown-item\" href=\"#\">设置</a></li>\n";
	Sidebar_tmp_stream << "        <li><a class=\"dropdown-item\" href=\"#\">属性</a></li>\n";
	Sidebar_tmp_stream << "        <li><hr class=\"dropdown-divider\"></li>\n";
	Sidebar_tmp_stream << "        <li><a class=\"dropdown-item\" href=\"/UserController/logOut\">注销</a></li>\n";
	Sidebar_tmp_stream << "      </ul>\n";
	Sidebar_tmp_stream << "    </div>\n";
	Sidebar_tmp_stream << "  </div>\n";
if(layoutName.empty())
{
std::string ret{std::move(Sidebar_tmp_stream.str())};
return ret;
}else
{
auto templ = DrTemplateBase::newTemplate(layoutName);
if(!templ) return "";
HttpViewData data = Sidebar_view_data;
auto str = std::move(Sidebar_tmp_stream.str());
if(!str.empty() && str[str.length()-1] == '\n') str.resize(str.length()-1);
data[""] = std::move(str);
return templ->genText(data);
}
}
