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
class QueueDAOImpl : public IndexQueueDAO {
    std::shared_ptr<pqxx::connection> conn;
    /*!
     * It's used in sql queries so that this class can be used
     * for loading different queries
     */

public:
    QueueDAOImpl ();
    QueueDAOImpl (std::shared_ptr<pqxx::connection> , std::string);
    ~QueueDAOImpl ();

    std::deque<std::string> getQueue () override;

    void saveQueue (std::deque<std::string>& ) override;


    void setConn (const std::shared_ptr<pqxx::connection> &conn) {
        QueueDAOImpl::conn = conn;
    }
};


#endif //CRAWLER_INDEXQUEUEDAOIMPL_H
