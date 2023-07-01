#pragma once


namespace docTo{
    void convertPdf(const char *inputFile, const char *outputFile, const char *commandLineFormat);
    void convertDocToPdf(const char *inputFile, const char *outputFile);
    void convertExcelToPdf(const char *inputFile, const char *outputFile);
    void convertPPTToPdf(const char *inputFile, const char *outputFile);
}