//
// Created by ololosh on 10/4/16.
//

#ifndef INDEXER_CRAWLERQUEUEDAO_H
#define INDEXER_CRAWLERQUEUEDAO_H

#include <memory>

#include <pqxx/pqxx>

#include "db/ICrawlerQueueDAO.h"

class CrawlerQueueDAO : public ICrawlerQueueDAO {
    std::shared_ptr<pqxx::connection> conn;

public:
    CrawlerQueueDAO () = delete;
    CrawlerQueueDAO (std::shared_ptr<pqxx::connection> );
    ~CrawlerQueueDAO () {};

    std::deque<std::string> loadQueue () override;

    void storeQueue (const std::deque<std::string>& ) override;
};


#endif //INDEXER_CRAWLERQUEUEDAO_H
