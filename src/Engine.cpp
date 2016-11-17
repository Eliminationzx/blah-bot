//
// Created by ololosh on 9/29/16.
//

#include <thread>
//#include <chrono>
#include <iostream>
#include <string>

#include "Engine.h"
#include "config/Config.h"

using namespace pqxx;
using namespace std;

Engine::Engine () {
}

void Engine::start () {
    logger->info (__PRETTY_FUNCTION__);

    Config conf;
    conf.loadFrom ("/home/ololosh/.config/indexer/indexer.conf");

//    if (conf.getString ("loggerPath"))

//    = spdlog::basic_logger_st (
//            "engine",
//            "/home/ololosh/pj/cpp/se/indexer/log/engine.log"
//    );

    running = true;
    int numberOfCrawlers = 2;

    auto posgresConn = make_shared<connection> (
            "user=postgres dbname=index_test"
    );

    indexQueueDAO = new IndexQueueDAO (posgresConn);
    crawlerQueueDAO = new CrawlerQueueDAO (posgresConn);
    crawlingQueue = make_shared<deque<string>> ();
    indexingQueue = make_shared<deque<Document>> ();

    *crawlingQueue = crawlerQueueDAO->loadQueue ();
    *indexingQueue = indexQueueDAO->getQueue ();

    auto indexingQueueMutex = make_shared<mutex> ();

    logger->info ("Loaded crawlingQueue: {} elements.", crawlingQueue->size ());
    logger->info ("Loaded indexingQueue: {} elements.", indexingQueue->size ());

    for (int i = 0; i < numberOfCrawlers; ++i)
    {
        crawlers.push_back (Crawler (i));
        crawlers.back ().setCrawlingQueue (crawlingQueue);
        crawlers.back ().setIndexingQueue (indexingQueue);
        crawlers.back ().setIndexingQueueMutex (indexingQueueMutex);
    }

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



