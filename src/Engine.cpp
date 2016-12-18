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

void Engine::start ()
{
    Config conf;
    conf.loadFrom ("/home/ololosh/.config/indexer/indexer.conf");

    auto loggerPath = conf.getString ("loggerPath");
    // default log file path
    if (!loggerPath)
        loggerPath = "/home/ololosh/.config/indexer/default.log";

    logger = spdlog::basic_logger_st (
            "engine",
            *loggerPath
    );

    running = true;
    int numberOfCrawlers = 1;
    int numberOfIndexers = 1;

    auto posgresConn = make_shared<connection> (
            "user=postgres dbname=index_test"
    );

    indexQueueDAO = new IndexQueueDAO (posgresConn);
    crawlerQueueDAO = new CrawlerQueueDAO (posgresConn);
    crawlingQueue = make_shared<deque<string>> ();
    indexingQueue = make_shared<deque<Document>> ();
    auto indexWriter = make_shared <IndexWriter> (posgresConn);

    *crawlingQueue = crawlerQueueDAO->loadQueue ();
    *indexingQueue = indexQueueDAO->getQueue ();

    auto indexingQueueMutex = make_shared<mutex> ();

//    logger->info ("Loaded crawlingQueue: {} elements.", crawlingQueue->size ());
//    logger->info ("Loaded indexingQueue: {} elements.", indexingQueue->size ());

    for (uint64_t i = 0; i < numberOfCrawlers; ++i)
    {
        crawlers.push_back (Crawler (i));
        crawlers.back ().setCrawlingQueue (crawlingQueue);
        crawlers.back ().setIndexingQueue (indexingQueue);
        crawlers.back ().setIndexingQueueMutex (indexingQueueMutex);

        if (loggerPath)
            crawlers.back ().setLogger (*loggerPath);
    }

    for (uint64_t i = 0; i < numberOfIndexers; ++i)
    {
        indexers.push_back (Indexer (i));
        indexers.back ().setIndexingQueue (indexingQueue);
        indexers.back ().setIndexingQueueMutex (indexingQueueMutex);
        indexers.back ().setIndexWriter (indexWriter);
    }

    for (const auto& e : crawlers) {
        workers.push_back (thread (e));
    }

    for (auto& e : indexers)
    {
        workers.push_back (thread (e));
    }
}

void Engine::stop () {
    logger->debug  (__PRETTY_FUNCTION__);

    for (auto& i : indexers)
        i.stop ();

    for (auto& c : crawlers) {
        c.stop ();
    }

    for (auto& w : workers)
        w.join ();

    crawlerQueueDAO->storeQueue (*crawlingQueue);
    indexQueueDAO->saveQueue (*indexingQueue);
}



