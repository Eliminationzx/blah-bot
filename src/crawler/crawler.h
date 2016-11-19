//
// Created by user on 7/25/16.
//

#ifndef CRAWLER_CRALWER_H
#define CRAWLER_CRALWER_H

#include <memory>
#include <queue>
#include <string>
#include <vector>
#include <mutex>
#include <iostream>
#include <atomic>

#include <pqxx/pqxx>
#include <spdlog/spdlog.h>

#include <db/IIndexQueueDAO.h>
#include "web/http.h"
#include "web/robotscontroller.h"
#include "index/Document.h"

/*!
 * Manages the indexing loop.
 * Stores a pointer to the crawling queue,
 * takes a page address from the queue and loads contents of the page
 */
class Crawler {
    uint64_t id;
    std::shared_ptr<web::HTTP> http;
    std::shared_ptr<web::RobotsController> robotstxt;
    static std::mutex crawlingQueueMutex;
    std::shared_ptr<std::deque<std::string>> crawlingQueue;
    std::shared_ptr<std::mutex> indexingQueueMutex;
    std::shared_ptr<std::deque<Document>> indexingQueue;
    std::shared_ptr<spdlog::logger> logger;
    bool running = false;

public:
    Crawler (uint64_t );
    ~Crawler ();

    void setCrawlingQueue (std::shared_ptr<std::deque<std::string>> );

    void setIndexingQueue (std::shared_ptr<std::deque<Document>> );

    void setIndexingQueueMutex (std::shared_ptr<std::mutex> );

    void init ();

    void operator () ();

    /*!
     * starts the indexing loop
     */
    void startLoop ();

    void stop ();

    void setLogger (std::string);
};


#endif //CRAWLER_CRALWER_H
