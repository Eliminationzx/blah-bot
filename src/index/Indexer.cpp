//
// Created by user on 7/26/16.
//
#include <cstdint>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "Document.h"
#include "parser/HTMLDocumentParser.h"
#include "Indexer.h"

using namespace std;
using namespace boost::filesystem;

Indexer::Indexer (uint64_t id)
{
    logger = spdlog::basic_logger_st (
            "worker #" + to_string (id),
            "/home/ololosh/pj/cpp/se/indexer/log/worker.log"
    );
    logger->set_level (spdlog::level::debug);
}

Indexer::~Indexer () {

}

void Indexer::setIndexingQueue (std::shared_ptr<std::deque<Document>> queue) {
    this->indexingQueue = queue;
}

void Indexer::setIndexingQueueMutex (shared_ptr<mutex> m)
{
    indexingQueueMutex = m;
}

void Indexer::start () const {
    // load a document from the queue
    // parse the document's source code
    // split the document's text into tokens
    // stem the tokens
    // add the tokens to the index
}

vector<string> Indexer::tokenize (std::string& text) const {
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

vector<string>& Indexer::stem (std::vector<std::string>& tokens) const {
    return tokens;
}

