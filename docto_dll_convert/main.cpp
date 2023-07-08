#pragma comment(lib, "docto.lib")

#include <iostream>

extern "C" {
void ConvertDocTo(const char* inputExtension, const char* inputFile, const char* outputFile, const char* outputFileExtension);
}

int main(int argc, char *argv[]) {

    const char *inputExtension = "-WD";
    const char *inputFile = "test.docx";
    const char *outputFile = "test.pdf";
    const char *outputFileExtension = "wdFormatPDF";
    
    ConvertDocTo(inputExtension, inputFile, outputFile, outputFileExtension);

    std::cout << 456 << std::endl;
    return 0;
}