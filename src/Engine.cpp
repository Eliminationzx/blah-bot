//
// Created by ololosh on 9/29/16.
//

#include <thread>
#include <functional>

#include "Engine.h"
#include "config/Config.h"

using namespace pqxx;
using namespace std;

Engine::Engine () {
}

void Engine::start () {
    Config conf;
    conf.loadFrom ("/home/ololosh/.config/indexer/indexer.conf");

    auto loggerPath = conf.getString ("loggerPath");
    // default log file path
    if (!loggerPath)
        loggerPath = "/home/ololosh/.config/indexer/default.log";

    logger = spdlog::basic_logger_mt (
            "engine",
            *loggerPath
    );

    auto crawlerThreadsNum = conf.getInt ("crawlerThreads");
    if (!crawlerThreadsNum)
        crawlerThreadsNum = 1;

    auto indexerThreadsNum = conf.getInt ("indexerThreads");
    if (!indexerThreadsNum)
        indexerThreadsNum = 1;

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

//    logger->info ("Loaded crawlingQueue: {} elements.", crawlingQueue->size ());
//    logger->info ("Loaded indexingQueue: {} elements.", indexingQueue->size ());

    for (int i = 0; i < *crawlerThreadsNum; ++i)
    {
        crawlers.push_back (Crawler (i));
        crawlers.back ().setCrawlingQueue (crawlingQueue);
        crawlers.back ().setIndexingQueue (indexingQueue);
        crawlers.back ().setIndexingQueueMutex (indexingQueueMutex);

        if (loggerPath)
            crawlers.back ().setLogger (*loggerPath);
    }

    for (auto& e : crawlers) {
        // pass a reference to the crawler object because
        // if the object is copied, it will not be possible to change it's state to stop it
        workers.push_back (move (thread (ref (e))));
    }
}

void Engine::stop () {
    logger->debug  (__PRETTY_FUNCTION__);

    for (auto& c : crawlers)
    {
        c.stop ();
    }

    for (auto& w : workers)
    {
        w.join ();
    }

    crawlerQueueDAO->storeQueue (*crawlingQueue);
    indexQueueDAO->saveQueue (*indexingQueue);
}



