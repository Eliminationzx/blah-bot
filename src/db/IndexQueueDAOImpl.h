//
// Created by user on 8/16/16.
//

#ifndef CRAWLER_INDEXQUEUEDAOIMPL_H
#define CRAWLER_INDEXQUEUEDAOIMPL_H

#include <memory>

#include <pqxx/pqxx>

#include "IndexQueueDAO.h"

/*!
 * IndexQueueDAO for postgresql
 */
class IndexQueueDAOImpl : public IndexQueueDAO {
    std::shared_ptr<pqxx::connection> conn;

public:
    IndexQueueDAOImpl ();
    IndexQueueDAOImpl (std::shared_ptr<pqxx::connection> );
    ~IndexQueueDAOImpl ();

    std::deque<std::string> getQueue () override;

    void saveQueue (std::deque<std::string>& ) override;
};


#endif //CRAWLER_INDEXQUEUEDAOIMPL_H
