#include <iostream>
#include "httplib.h"

int main() {
    httplib::Server svr;
    // 静态文件路由，返回本地的 Bootstrap CSS 和 JavaScript 文件
    svr.set_base_dir("./static");
    std::cout<<"---------"<<std::endl;
    svr.listen("localhost", 8080);

    return 0;
}