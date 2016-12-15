//
// Created by user on 7/26/16.
//
#include <cstdint>
#include <iostream>

#include "Document.h"
#include "parser/HTMLDocumentParser.h"
#include "Indexer.h"
#include "Stemmer.h"

using namespace std;

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

void Indexer::start ()
{
    Document doc (make_shared <HTMLDocumentParser> ());
    size_t newEnd = 0;

    while (running)
    {
        // load a document from the queue
        if (!indexingQueue->empty ())
        {
            indexingQueueMutex->lock ();

            doc = indexingQueue->front ();
            indexingQueue->pop_front ();

            indexingQueueMutex->unlock ();
        }


        // parse the document's source code
        if (!doc.parse ())
            continue;

        // split the document's text into tokens
        doc.setTokens (tokenize (doc.getHtml ()));

        // stem the tokens
        for (auto& token : doc.getTokens ())
        {
            newEnd = stem (const_cast <char*> (token.data ()), 0, token.size () - 1);

            token = string (token, 0, newEnd + 1);
        }

        // TODO: all that stuff
        // count term frequency
        // count inverted document frequency
        // count documents length
//        doc.getTokens ().size ();

        // TODO: indexWriter
        // add the tokens to the index
    }
}

vector<string> Indexer::tokenize (const std::string& text)  {
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


