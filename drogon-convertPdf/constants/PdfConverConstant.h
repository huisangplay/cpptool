#pragma once
//
// Created by ZHOU on 2023/7/1.
//

#ifndef DROGON_CONVERTPDF_PDFCONVERCONSTANT_H
#define DROGON_CONVERTPDF_PDFCONVERCONSTANT_H

namespace pdfConvertConstant{
    static const char* CONVERT_PDF_FAILED="pdf转换失败，请检查是否为加密文件或非支持文件";
    static const char* CONVERT_UPLOAD_FAILED="必须上传一个文件";
    static const char* CONVERT_SERVICE_MONITOR="pdfService is running...";
    static const int PDF_CONVERT_WAITING_TIME=5 * 60 * 1000;
}

#endif //DROGON_CONVERTPDF_PDFCONVERCONSTANT_H
