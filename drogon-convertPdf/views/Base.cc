//this file is generated by program(drogon_ctl) automatically,don't modify it!
#include "Base.h"
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
 #include"../constants/MessageConstant.h" 
using namespace drogon;
std::string Base::genText(const DrTemplateData& Base_view_data)
{
	drogon::OStringStream Base_tmp_stream;
	std::string layoutName{""};
	Base_tmp_stream << "<!--公共引入文件-->\n";
	Base_tmp_stream << "<link rel=\"stylesheet\" type=\"text/css\" href=\"/static/css/bootstrap.min.css\"/>\n";
	Base_tmp_stream << "<script src=\"/static/js/bootstrap.bundle.min.js\"></script>\n";
	Base_tmp_stream << "<script src=\"/static/jquery/jquery-3.7.0.min.js\"></script>\n";
Base_tmp_stream<<"\n";
	Base_tmp_stream << "<!--消息提示-->\n";
	Base_tmp_stream << "<svg xmlns=\"http://www.w3.org/2000/svg\" style=\"display: none;\">\n";
	Base_tmp_stream << "    <symbol id=\"check-circle-fill\" fill=\"currentColor\" viewBox=\"0 0 16 16\">\n";
	Base_tmp_stream << "        <path d=\"M16 8A8 8 0 1 1 0 8a8 8 0 0 1 16 0zm-3.97-3.03a.75.75 0 0 0-1.08.022L7.477 9.417 5.384 7.323a.75.75 0 0 0-1.06 1.06L6.97 11.03a.75.75 0 0 0 1.079-.02l3.992-4.99a.75.75 0 0 0-.01-1.05z\"/>\n";
	Base_tmp_stream << "    </symbol>\n";
	Base_tmp_stream << "    <symbol id=\"info-fill\" fill=\"currentColor\" viewBox=\"0 0 16 16\">\n";
	Base_tmp_stream << "        <path d=\"M8 16A8 8 0 1 0 8 0a8 8 0 0 0 0 16zm.93-9.412-1 4.705c-.07.34.029.533.304.533.194 0 .487-.07.686-.246l-.088.416c-.287.346-.92.598-1.465.598-.703 0-1.002-.422-.808-1.319l.738-3.468c.064-.293.006-.399-.287-.47l-.451-.081.082-.381 2.29-.287zM8 5.5a1 1 0 1 1 0-2 1 1 0 0 1 0 2z\"/>\n";
	Base_tmp_stream << "    </symbol>\n";
	Base_tmp_stream << "    <symbol id=\"exclamation-triangle-fill\" fill=\"currentColor\" viewBox=\"0 0 16 16\">\n";
	Base_tmp_stream << "        <path d=\"M8.982 1.566a1.13 1.13 0 0 0-1.96 0L.165 13.233c-.457.778.091 1.767.98 1.767h13.713c.889 0 1.438-.99.98-1.767L8.982 1.566zM8 5c.535 0 .954.462.9.995l-.35 3.507a.552.552 0 0 1-1.1 0L7.1 5.995A.905.905 0 0 1 8 5zm.002 6a1 1 0 1 1 0 2 1 1 0 0 1 0-2z\"/>\n";
	Base_tmp_stream << "    </symbol>\n";
	Base_tmp_stream << "</svg>\n";
 char const * message_warning=Base_view_data.get<char const *>(message::MESSAGE_WARNING_DEFINITION);
      char const * message_info=Base_view_data.get<char const *>(message::MESSAGE_INFO_DEFINITION);
 if(message_warning!=nullptr&&strlen(message_warning)!=0){
	Base_tmp_stream << "<div class=\"alert alert-warning alert-dismissible fade show\" role=\"alert\" style=\" position: fixed;transform: translate(-50%, 0); top: 0;left: 50%; width: 500px; height: 60px;\">\n";
	Base_tmp_stream << "    <svg class=\"bi flex-shrink-0 me-2\" width=\"24\" height=\"24\" role=\"img\" aria-label=\"Warning:\">\n";
	Base_tmp_stream << "        <use xlink:href=\"#exclamation-triangle-fill\"/>\n";
	Base_tmp_stream << "    </svg>\n";
	Base_tmp_stream << "    <strong>";
{
    auto & val=Base_view_data["message_warning"];
    if(val.type()==typeid(const char *)){
        Base_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        Base_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
	Base_tmp_stream << "</strong>\n";
	Base_tmp_stream << "</div>\n";
 }
 if(message_info!=nullptr&&strlen(message_info)!=0){
	Base_tmp_stream << "<div class=\"alert alert-success alert-dismissible fade show\" role=\"alert\" style=\" position: fixed;transform: translate(-50%, 0); top: 0;left: 50%; width: 500px; height: 60px;\">\n";
	Base_tmp_stream << "    <svg class=\"bi flex-shrink-0 me-2\" width=\"24\" height=\"24\" role=\"img\" aria-label=\"Success:\">\n";
	Base_tmp_stream << "        <use xlink:href=\"#check-circle-fill\"/>\n";
	Base_tmp_stream << "    </svg>\n";
	Base_tmp_stream << "    <strong> ";
{
    auto & val=Base_view_data["message_info"];
    if(val.type()==typeid(const char *)){
        Base_tmp_stream<<*any_cast<const char *>(&val);
    }else if(val.type()==typeid(std::string)||val.type()==typeid(const std::string)){
        Base_tmp_stream<<*any_cast<const std::string>(&val);
    }
}
	Base_tmp_stream << "</strong>\n";
	Base_tmp_stream << "</div>\n";
 }
Base_tmp_stream<<"\n";
	Base_tmp_stream << "<script type=\"text/javascript\">\n";
	Base_tmp_stream << "    $(document).ready(function () {\n";
	Base_tmp_stream << "        $(\".alert-dismissible\").fadeOut(3000, function() {\n";
	Base_tmp_stream << "                                    alertElement.remove();\n";
	Base_tmp_stream << "                                  });\n";
	Base_tmp_stream << "    });\n";
	Base_tmp_stream << "</script>\n";
if(layoutName.empty())
{
std::string ret{std::move(Base_tmp_stream.str())};
return ret;
}else
{
auto templ = DrTemplateBase::newTemplate(layoutName);
if(!templ) return "";
HttpViewData data = Base_view_data;
auto str = std::move(Base_tmp_stream.str());
if(!str.empty() && str[str.length()-1] == '\n') str.resize(str.length()-1);
data[""] = std::move(str);
return templ->genText(data);
}
}