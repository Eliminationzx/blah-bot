//
// Created by user on 7/25/16.
//

#ifndef CRAWLER_CRALWER_H
#define CRAWLER_CRALWER_H

#include <memory>
#include <queue>
#include <string>
#include <vector>

#include <pqxx/pqxx>
#include <spdlog/spdlog.h>

#include <db/IndexQueueDAO.h>
#include "web/http.h"
#include "web/robotscontroller.h"
#include "HTML/htmlParser.h"
#include <index/indexator.h>
#include "db/PageDAO.h"

/*!
 * Manages the indexing loop
 */
class Crawler {
    std::shared_ptr<web::HTTP> http;
    std::shared_ptr<web::RobotsController> robotstxt;
    std::deque<std::string> queue;
//    std::shared_ptr<pqxx::connection> indexDb;
    IndexQueueDAO* queuedb;
    htmlParser html;
    Indexator indexator;
    PageDAO* pagedb;
    std::shared_ptr<spdlog::logger> logger = spdlog::basic_logger_st (
            "crawler",
            "/home/ololosh/pj/cpp/se/crawler/log/crawler.log"
    );

public:
    Crawler ();
    ~Crawler ();

    void init ();

    /*!
     * starts indexing loop
     */
    void start ();
};


#endif //CRAWLER_CRALWER_H
