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

    this->queue = this->queuedb->getQueue ();
}

void Crawler::start () {
    Page page;
    string htmlroot = "/home/ololosh/pj/cpp/se/sourceDir/";

    while (!this->queue.empty ()) {
        page.address = queue.front ();
        queue.pop_front ();

        logger->info ("downloading page from: {0}", page.address);

        if (robotstxt->allowed (page.address))
            page.html = http->get (page.address);
        else
            logger->info ("the page is disallowed");

        page.links = html.extractLinks (page.html);

//        while (!page.links.empty ()) {
//            queue.push_back (move (page.links.back ()));
//            page.links.pop_back ();
//        }

        pagedb->saveURL (page);

        logger->info ("Saving file: {}", htmlroot + to_string (page.id));

        ofstream f (htmlroot + to_string (page.id));

        if (f.is_open ())
            f << page.html;

        f.close ();

        this_thread::sleep_for (std::chrono::milliseconds (500));
    }

    queuedb->saveQueue (queue);
}

