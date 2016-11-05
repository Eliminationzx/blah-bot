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

mutex Crawler::crawlingQueueMutex;

Crawler::Crawler (uint64_t id)
    : http (make_shared<HTTP> ()),
      robotstxt (make_shared<RobotsController> (http, make_shared<RobotstxtDb> ()))
{
    this->id = id;

    logger = spdlog::basic_logger_mt (
            "crawler #" + std::to_string (id),
            "/home/ololosh/pj/cpp/se/indexer/log/crawler.log"
    );
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

void Crawler::setIndexingQueueMutex (shared_ptr<mutex> m)
{
    indexingQueueMutex = m;
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

void Crawler::startLoop ()
{
    logger->info ("Crawler has started: {}", this_thread::get_id ());

    auto htmlParser = make_shared<HTMLDocumentParser> ();
    Document htmlDocument (htmlParser);
    string address;
    vector<string> links;

    while (running) {
        // КОСТЫЛЬ
        // TODO: if the queue is empty - wait until there is a link to crawl (idle state)
        if (crawlingQueue->empty ())
        {
            logger->info ("The queue is emtpy, exiciting the loop");

            return;
        }

        address = string (move (crawlingQueue->front ()));

        crawlingQueueMutex.lock ();
        crawlingQueue->pop_front ();
        crawlingQueueMutex.unlock ();

        logger->info ("downloading page from: {0}", address);

        if (robotstxt->allowed (address)) {
            htmlDocument.setHtml (move (http->get (address)));

            logger->info ("the page has been downloaded");

            // If the document is not valid just go to the next in the queue
//            if (!htmlDocument.isValid ())
//                continue;

        } else {
            logger->info ("the page is disallowed");
        }

        htmlDocument.setAddress (move (address));

        links = move (htmlParser->extractLinks (htmlDocument.getHtml ()));

        logger->info ("Extracting {} links.", links.size ());

        crawlingQueueMutex.lock ();
        while (!links.empty ()) {
            crawlingQueue->push_back (move (links.back ()));
            links.pop_back ();
        }
        crawlingQueueMutex.unlock ();

        indexingQueueMutex->lock ();
        indexingQueue->push_back (htmlDocument);
        indexingQueueMutex->unlock ();

        logger->info ("The page has been added to the indexing queue: {}", htmlDocument.getAddress ());

        this_thread::sleep_for (std::chrono::milliseconds (500));
    }
}

void Crawler::stop () {
    logger->info ("Stoping the crawler");

    running = false;
}