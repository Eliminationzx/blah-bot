//
// Created by user on 7/25/16.
//

#include <fstream>
#include <thread>
#include <chrono>

#include "db/IndexQueueDAOImpl.h"
#include "db/Pagedb.h"
#include "db/robotstxtDb.h"
#include "web/Page.h"
#include "crawler.h"

using namespace std;
using namespace web;

Crawler::Crawler ()
    : http (make_shared<HTTP> ()),
      robotstxt (make_shared<RobotsController> (http, make_shared<RobotstxtDb> ()))
{
    this->queuedb = new IndexQueueDAOImpl ();
    pagedb = new Pagedb ();
}

Crawler::~Crawler () {
    delete queuedb;
    delete pagedb;
}

void Crawler::init () {
    logger->info ("Crawler initialization");

//    this->crawlingQueue = this->queuedb->getQueue ();
}

void Crawler::operator () () {
    if (crawlingQueue == nullptr)
        return;

    startLoop ();
}

void Crawler::startLoop () {
    Page page;
    string htmlroot = "/home/ololosh/pj/cpp/se/sourceDir/";

    while (!this->crawlingQueue->empty ()) {
        page.address = crawlingQueue->front ();

        crawlingQueueMutex.lock ();
        crawlingQueue->pop_front ();
        crawlingQueueMutex.unlock ();

        logger->info ("downloading page from: {0}", page.address);

        if (robotstxt->allowed (page.address))
            page.html = http->get (page.address);
        else
            logger->info ("the page is disallowed");

        // TODO: replace for Document class
//        page.links = html.extractLinks (page.html);

        crawlingQueueMutex.lock ();
        while (!page.links.empty ()) {
            crawlingQueue->push_back (move (page.links.back ()));
            page.links.pop_back ();
        }
        crawlingQueueMutex.unlock ();

        pagedb->saveURL (page);

        // TODO: replace copying for moving
        indexingQueueMutex.lock ();
        indexingQueue->push_back (page);
        indexingQueueMutex.unlock ();

        this_thread::sleep_for (std::chrono::milliseconds (500));
    }

    queuedb->saveQueue (*crawlingQueue);
}

