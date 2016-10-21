//
// Created by ololosh on 10/4/16.
//

#ifndef INDEXER_ICRAWLERQUEUEDAO_H
#define INDEXER_ICRAWLERQUEUEDAO_H

#include <deque>
#include <string>


class ICrawlerQueueDAO {
public:
    virtual ~ICrawlerQueueDAO () {};

    virtual std::deque<std::string> loadQueue () = 0;
    virtual void storeQueue (const std::deque<std::string>& ) = 0;
};


#endif //INDEXER_ICRAWLERQUEUEDAO_H
