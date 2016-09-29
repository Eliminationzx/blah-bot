//
// Created by user on 8/16/16.
//

#ifndef CRAWLER_INDEXQUEUEDAO_H
#define CRAWLER_INDEXQUEUEDAO_H

#include <deque>
#include <string>

class IndexQueueDAO {
public:
    virtual ~IndexQueueDAO () {};

    virtual std::deque<std::string> getQueue () = 0;
    virtual void saveQueue (std::deque<std::string>& ) = 0;
};

#endif //CRAWLER_INDEXQUEUEDAO_H

