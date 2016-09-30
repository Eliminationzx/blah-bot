//
// Created by user on 8/16/16.
//

#ifndef CRAWLER_INDEXQUEUEDAOIMPL_H
#define CRAWLER_INDEXQUEUEDAOIMPL_H

#include <memory>

#include <pqxx/pqxx>

#include "QueueDAO.h"

/*!
 * QueueDAO for postgresql
 */
class QueueDAOImpl : public QueueDAO {
    std::shared_ptr<pqxx::connection> conn;
    /*!
     * It's used in sql queries so that this class can be used
     * for loading different queries
     */
    std::string tableName;

public:
    QueueDAOImpl ();
    QueueDAOImpl (std::shared_ptr<pqxx::connection> , std::string);
    ~QueueDAOImpl ();

    std::deque<std::string> getQueue () override;

    void saveQueue (std::deque<std::string>& ) override;


    void setConn (const std::shared_ptr<pqxx::connection> &conn) {
        QueueDAOImpl::conn = conn;
    }

    void setTableName (const std::string &tableName) {
        QueueDAOImpl::tableName = tableName;
    }
};


#endif //CRAWLER_INDEXQUEUEDAOIMPL_H
