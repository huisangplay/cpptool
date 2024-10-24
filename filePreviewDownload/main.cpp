#include <iostream>
#include <fstream>
#include "util/httplib.h"
#include"Service.h"

int main() {
    Server server;

    server.Get("/userGuideFile/uploadFile", showUploadPage);

    server.Post("/userGuideFile/upload", uploadFile);

    server.Get("/userGuideFile/fileList", showFileList);

    server.Get("/userGuideFile/preview", filePreview);

    server.Get("/userGuideFile/downloadAllFiles", downloadAllFiles);

    std::cout << "Starting server on http://localhost:8080" << std::endl;

    server.listen("0.0.0.0", 8080);

    return 0;
}
