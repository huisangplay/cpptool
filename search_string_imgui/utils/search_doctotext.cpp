#include "search_doctotext.h"
bool search_doctotext(std::string filepath, std::string findstr){
    std::string content;
    DocToTextExtractorParams* params = doctotext_create_extractor_params();
    DocToTextFormattingStyle* style = doctotext_create_formatting_style();
    doctotext_formatting_style_set_url_style(style, DOCTOTEXT_URL_STYLE_EXTENDED);
    doctotext_extractor_params_set_verbose_logging(params, 1);
    doctotext_extractor_params_set_formatting_style(params, style);
    //Extract text
    DocToTextExtractedData* data = doctotext_process_file(filepath.c_str(), params, NULL);
    //We should check if "data" is NULL!
    //printf("\n\ndata: %s\n", doctotext_extracted_data_get_text(data));
    if(data!=NULL) content=doctotext_extracted_data_get_text(data);
    //We have to release those data:
    doctotext_free_extracted_data(data);
    doctotext_free_extractor_params(params);
    doctotext_free_formatting_style(style);
    if(content.find(GBK_2_UTF8(findstr))!=std::string::npos) return true;
    else return false;
}