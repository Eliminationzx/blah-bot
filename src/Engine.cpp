//
// Created by ololosh on 9/29/16.
//

#include <thread>
//#include <chrono>
#include <iostream>
#include <string>

#include "Engine.h"

using namespace pqxx;
using namespace std;

Engine::Engine () {
}

// TODO: init implementation
void Engine::start () {
    logger->debug (__PRETTY_FUNCTION__);

    running = true;

    string input;
    auto posgresConn = make_shared<connection> (
            "user=postgres dbname=index_test"
    );

    indexQueueDAO = new IndexQueueDAO (posgresConn);
    crawlerQueueDAO = new CrawlerQueueDAO (posgresConn);
    crawlingQueue = make_shared<deque<string>> ();
    indexingQueue = make_shared<deque<Document>> ();

    *crawlingQueue = crawlerQueueDAO->loadQueue ();
    *indexingQueue = indexQueueDAO->getQueue ();

    Crawler c;
    c.setCrawlingQueue (crawlingQueue);
    c.setIndexingQueue (indexingQueue);

    crawlers.push_back (c);

    for (const auto& e : crawlers) {
        workers.push_back (thread (e));
    }
}

void Engine::stop () {
    logger->debug  (__PRETTY_FUNCTION__);

    for (auto& c : crawlers) {
        c.stop ();
    }

    crawlerQueueDAO->storeQueue (*crawlingQueue);
    indexQueueDAO->saveQueue (*indexingQueue);
}



