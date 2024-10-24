//
// Created by ZHOU on 24-10-23.
//

#ifndef UPLOADHTML_H
#define UPLOADHTML_H

const char *uploadHtml = R"(
<!DOCTYPE html>
<html lang="en">

  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Upload File</title></head>

  <body>
    <div class="container">
      <h1>文件上传</h1>
      <form action="/userGuideFile/upload" method="post" enctype="multipart/form-data">
        <select name="fileDescribe" id="fileDescribe" type="text">
          <option value="XBOM操作手册">XBOM操作手册</option>
          <option value="XBOM操作视频">XBOM操作视频</option>
          <option value="构型业务主管负责人">构型业务主管负责人</option>
        </select>
        <label for="file" class="drop-container">
          <input type="file" id="file" name="uploadFile" required>
        </label>
        <button type="submit">上传</button>
      </form>
    </div>
  </body>

</html>
)";

#endif //UPLOADHTML_H
