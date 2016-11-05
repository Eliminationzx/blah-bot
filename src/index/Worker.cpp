//
// Created by user on 7/26/16.
//
#include <cstdint>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "Document.h"
#include "parser/HTMLDocumentParser.h"
#include "Worker.h"

using namespace std;
using namespace boost::filesystem;

Worker::Worker () {
    logger->set_level (spdlog::level::debug);
}

Worker::~Worker () {

}

void Worker::start () const {
    // get the file's id from the file's name
    // load the file's url from the db
    // split the document's text into tokens
    // stem the tokens
    // add the tokens to the index
    // delete the file from the filesystem

}

vector<string> Worker::tokenize (std::string& text) const {
    vector<string> tokens;
    size_t prevPos = 0;
    bool isAlnum = false;

    /*
     */
    for (size_t i = 0; i < text.length(); ++i)
    {
        if (!isalnum (text[i]))
        {
            if (isAlnum)
                continue;

            tokens.emplace_back (text, prevPos, i - prevPos);

            isAlnum = true;
        }
        else if (isAlnum)
        {
            prevPos = i;
            isAlnum = false;
        }
    }

    return tokens;
}

vector<string>& Worker::stem (std::vector<std::string>& tokens) const {
    return tokens;
}

