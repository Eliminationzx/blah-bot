//
// Created by ololosh on 10/4/16.
//

#ifndef INDEXER_ICRAWLERQUEUEDAO_H
#define INDEXER_ICRAWLERQUEUEDAO_H

#include <deque>

#include "index/Document.h"

class ICrawlerQueueDAO {
public:
    virtual ~ICrawlerQueueDAO () {};

    virtual std::deque<Document> loadQueue () = 0;
    virtual void storeQueue (const std::deque<Document>& ) = 0;
};


#endif //INDEXER_ICRAWLERQUEUEDAO_H
