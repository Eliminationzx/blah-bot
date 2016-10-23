//
// Created by ololosh on 9/29/16.
//

#ifndef INDEXER_ENGINE_H
#define INDEXER_ENGINE_H

#include <memory>
#include <deque>
#include <thread>

#include "spdlog/spdlog.h"

#include "crawler/crawler.h"
#include "index/Worker.h"

/*!
 * Starts up crawling and indexing workers.
 * Manages the load balancing between the workers
 */
class Engine {
    // TODO: crawlingQueue source
    // TODO: indexingQueue source
    std::shared_ptr<std::deque<std::string>> crawlingQueue;
//    std::shared_ptr<std::deque<Page>> indexingQueue;
    std::deque<Crawler> crawlers;
    std::deque<Worker> indexers;
    std::deque<std::thread> workers;
    std::shared_ptr<spdlog::logger> logger = spdlog::basic_logger_st (
            "engine",
            "/home/ololosh/pj/cpp/se/indexer/log/engine.log"
    );
    bool running = false;

public:
    Engine () = default;
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
