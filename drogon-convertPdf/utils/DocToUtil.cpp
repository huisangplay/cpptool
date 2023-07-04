#include <windows.h>
#include <cstdio>
#include "DocToUtil.h"
#include "../constants/PdfConverConstant.h"
#include<string>

namespace docTo {
    void convertPdf(const char *inputFile, const char *outputFile, const char *commandLineFormat) {

        char cmdLine[MAX_PATH];

        sprintf_s(cmdLine, MAX_PATH, commandLineFormat, inputFile, outputFile);
        // Create DocTo process
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        ZeroMemory(&pi, sizeof(pi));
        si.cb = sizeof(si);
        if (!CreateProcessA(NULL, cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            return;
        }

        DWORD wait_result = WaitForSingleObject(pi.hProcess, pdfConvertConstant::PDF_CONVERT_WAITING_TIME);

        TerminateProcess(pi.hProcess, 0);
        if (wait_result == WAIT_TIMEOUT) { // 如果等待超时
            TerminateProcess(pi.hProcess, 0); // 强制结束进程

            HWND hWnd = FindWindowA(NULL, "密码");

            if (hWnd != NULL) {
                // 发送 WM_CLOSE 消息给窗口
                SendMessage(hWnd, WM_CLOSE, 0, 0);
            }
        }

        // Close process and thread handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    void convertDocToPdf(const char *inputFile, const char *outputFile) {
        convertPdf(inputFile, outputFile, R"(docto.exe -f "%s" -O  "%s" -T wdFormatPDF  -X true -Q)");
    }

    void convertExcelToPdf(const char *inputFile, const char *outputFile) {
        convertPdf(inputFile, outputFile, R"(docto.exe -XL -f "%s" -O  "%s" -T xlPDF  -X true -Q)");
    }

    void convertPPTToPdf(const char *inputFile, const char *outputFile) {
        convertPdf(inputFile, outputFile, R"(docto.exe -PP -f "%s" -o  "%s" -T ppSaveAsPDF -X true -Q)");
    }
}