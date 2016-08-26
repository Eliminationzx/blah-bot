//
// Created by user on 7/26/16.
//
#include <cstdint>

#include "Worker.h"

using namespace std;

Worker::Worker () {

}

Worker::~Worker () {

}

void Worker::start (Document& page) const {

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

