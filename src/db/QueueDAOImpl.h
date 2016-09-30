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

public:
    QueueDAOImpl ();
    QueueDAOImpl (std::shared_ptr<pqxx::connection> );
    ~QueueDAOImpl ();

    std::deque<std::string> getQueue () override;

    void saveQueue (std::deque<std::string>& ) override;
};


#endif //CRAWLER_INDEXQUEUEDAOIMPL_H
