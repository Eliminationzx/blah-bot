//
// Created by user on 8/19/16.
//

#include <string>

#include <gmock/gmock.h>

#include "parser/HTMLDocumentParser.h"

using namespace std;

TEST (htmlDocumentPaserTest, checkDocumentValidity) {
    HTMLDocumentParser p;
    string html = "<!doctype html>";
    string html2 = "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01//EN' 'http://www.w3.org/TR/html4/strict.dtd'>";
    string html3 =  "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">";
//    string html4 = "";
//    string html5 = "";
//    string html6 = "";
//    string html7 = "";
//    string html8 = "";

    ASSERT_TRUE (p.isValid (html));
    ASSERT_TRUE (p.isValid (html2));
    ASSERT_TRUE (p.isValid (html3));
}

