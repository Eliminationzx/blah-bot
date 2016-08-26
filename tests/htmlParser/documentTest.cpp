//
// Created by ololosh on 8/26/16.
//

#include <string>

#include <gmock/gmock.h>

#include "index/Document.h"
#include "parser/DocumentParser.h"

using namespace std;
using ::testing::Return;

std::string html =
R"(<!doctype html>
<html>
<head>
    <title>Example Domain</title>

    <meta charset="utf-8" />
    <meta http-equiv="Content-type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style type="text/css">
    body {
        background-color: #f0f0f2;
        margin: 0;
        padding: 0;
        font-family: "Open Sans", "Helvetica Neue", Helvetica, Arial, sans-serif;

    }
    div {
        width: 600px;
        margin: 5em auto;
        padding: 50px;
        background-color: #fff;
        border-radius: 1em;
    }
    a:link, a:visited {
        color: #38488f;
        text-decoration: none;
    }
    @media (max-width: 700px) {
        body {
            background-color: #fff;
        }
        div {
            width: auto;
            margin: 0 auto;
            border-radius: 0;
            padding: 1em;
        }
    }
    </style>
</head>

<body>
<div>
    <h1>Example Domain</h1>
    <p>This domain is established to be used for illustrative examples in documents. You may use this domain in examples without prior coordination or asking for permission.</p>
    <p><a href="http://www.iana.org/domains/example">More information...</a></p>
</div>
</body>
</html>)";

std::string expectedText = "Example Domain Example Domain "
        "This domain is established to be used for illustrative examples in documents. You may use this "
        "domain in examples without prior coordination or asking for permission. "
        "More information...";

class MockDocumentParser : public DocumentParser {
public:
    MOCK_CONST_METHOD1 (isValid, bool (const std::string&));
    MOCK_CONST_METHOD1 (extractText, std::string (const std::string&));
};

class DocumentTestFixture : public ::testing::Test {
public:
    MockDocumentParser* parser = nullptr;
    Document* doc = nullptr;

    DocumentTestFixture () {
        parser = new MockDocumentParser;

        EXPECT_CALL (*parser, isValid (html))
                     .WillOnce (Return (true));
        EXPECT_CALL (*parser, extractText (html))
                     .WillOnce (Return (expectedText));
    }

    ~DocumentTestFixture() {
        delete parser;
    }

    void SetUp () {
        Document* doc = new Document (parser);
    }

    void TearDown () {
        delete doc;
    }
};

TEST_F (DocumentTestFixture, shouldParseHTML) {
    ASSERT_TRUE (doc->setHtml (html));
    ASSERT_TRUE (doc->parse ());

//    ASSERT_STREQ (doc->getText.c_str (), expectedText.c_str ());
}
