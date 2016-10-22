//
// Created by user on 8/16/16.
//

#ifndef CRAWLER_INDEXQUEUEDAO_H
#define CRAWLER_INDEXQUEUEDAO_H

#include <deque>
#include <string>

#include "index/Document.h"


class IIndexQueueDAO {
public:
    virtual ~IIndexQueueDAO () {};

    virtual std::deque<Document> getQueue () = 0;
    virtual void saveQueue (std::deque<Document>& ) = 0;
};

#endif //CRAWLER_INDEXQUEUEDAO_H

