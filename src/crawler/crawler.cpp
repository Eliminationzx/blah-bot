//
// Created by user on 7/25/16.
//

#include <fstream>
#include <thread>
#include <chrono>

#include "db/IndexQueueDAO.h"
#include "db/robotstxtDb.h"
#include "crawler.h"

using namespace std;
using namespace web;

Crawler::Crawler ()
    : http (make_shared<HTTP> ()),
      robotstxt (make_shared<RobotsController> (http, make_shared<RobotstxtDb> ()))
{
}

Crawler::~Crawler () { }

void Crawler::init () {
    logger->info ("Crawler initialization");
}

void Crawler::setCrawlingQueue (std::shared_ptr<std::deque<std::string>> queue) {
    this->crawlingQueue = queue;
}

void Crawler::setIndexingQueue (std::shared_ptr<std::deque<Document>> queue) {
    this->indexingQueue = queue;
}

void Crawler::operator () () {
    if (crawlingQueue == nullptr) {
        logger->error ("Unable to start: crawling queue is not specified.");

        return;
    }

    if (indexingQueue == nullptr) {
        logger->error ("Unable to start: indexing queue is not specified.");

        return;
    }

    running = true;

    startLoop ();
}

void Crawler::startLoop () {
    auto htmlParser = make_shared<HTMLDocumentParser> ();
    Document htmlDocument (htmlParser);
    string address;
    vector<string> links;

    while (running) {
        address = move (crawlingQueue->front ());

        crawlingQueueMutex.lock ();
        crawlingQueue->pop_front ();
        crawlingQueueMutex.unlock ();

        logger->info ("downloading page from: {0}", address);

        if (robotstxt->allowed (address)) {
            htmlDocument.setHtml (move (http->get (address)));

            // If the document is not valid just go to the next in the queue
            if (!htmlDocument.isValid ())
                continue;

        } else {
            logger->info ("the page is disallowed");
        }

        htmlDocument.setAddress (move (address));

        links = move (htmlParser->extractLinks (htmlDocument.getHtml ()));

        crawlingQueueMutex.lock ();
        while (!links.empty ()) {
            crawlingQueue->push_back (move (links.back ()));
            links.pop_back ();
        }
        crawlingQueueMutex.unlock ();

        indexingQueueMutex.lock ();
        indexingQueue->push_back (htmlDocument);
        indexingQueueMutex.unlock ();

        this_thread::sleep_for (std::chrono::milliseconds (500));
    }
}

void Crawler::stop () {
    logger->info ("Stoping the crawler");

    running = false;
}