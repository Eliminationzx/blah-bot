//
// Created by ololosh on 9/29/16.
//

#ifndef INDEXER_ENGINE_H
#define INDEXER_ENGINE_H

#include <memory>
#include <deque>
#include <thread>

#include "spdlog/spdlog.h"
#include <pqxx/pqxx>

#include "crawler/crawler.h"
#include "index/Indexer.h"
#include "index/Document.h"
#include "db/CrawlerQueueDAO.h"
#include "db/IndexQueueDAO.h"

/*!
 * Starts up crawling and indexing workers.
 * Manages the load balancing between the workers
 */
class Engine {
    ICrawlerQueueDAO* crawlerQueueDAO = nullptr;
    IIndexQueueDAO* indexQueueDAO = nullptr;
    std::shared_ptr<std::deque<std::string>> crawlingQueue;
    std::shared_ptr<std::deque<Document>> indexingQueue;
    std::deque<Crawler> crawlers;
    std::deque<Indexer> indexers;
    std::deque<std::thread> workers;
    std::shared_ptr<spdlog::logger> logger;
    bool running = false;

public:
    Engine ();
    Engine (const Engine& ) = delete;
    Engine (Engine&& ) = delete;
    ~Engine () = default;

    /*!
     * Loads the crawling and indexing queues.
     * Starts the worker threads.
     *
     */
    void start ();

    void stop ();
};


#endif //INDEXER_ENGINE_H
