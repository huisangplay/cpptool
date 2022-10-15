//
// Created by huisa on 2022/10/14.
//

#include "search_pdf.h"
bool search_pdf(std::string filepath, std::string findstr)
{
    const char*    pszInput;
    TextExtractor extractor;
    pszInput  = filepath.c_str();

    if( !pszInput )
    {
        return false;
    }
    try {
        string content_string;
        PdfMemDocument document( pszInput );

        int nCount = document.GetPageCount();
        for( int i=0; i<nCount; i++ )
        {
            PdfPage* pPage = document.GetPage( i );
            content_string+=extractor.ExtractText( &document, pPage );
            string_replace(content_string,"\n","");
            if(content_string.find(findstr)!=string::npos) return true;
        }

    } catch( PdfError & e ) {
        return false;
    }
    return false;
}