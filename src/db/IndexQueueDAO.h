//
// Created by user on 8/16/16.
//

#ifndef CRAWLER_INDEXQUEUEDAOIMPL_H
#define CRAWLER_INDEXQUEUEDAOIMPL_H

#include <memory>

#include <pqxx/pqxx>

#include "IIndexQueueDAO.h"
#include "index/Document.h"

/*!
 * IIndexQueueDAO for postgresql
 */
class IndexQueueDAO : public IIndexQueueDAO {
    std::shared_ptr<pqxx::connection> conn;
    /*!
     * It's used in sql queries so that this class can be used
     * for loading different queries
     */

public:
    IndexQueueDAO ();
    IndexQueueDAO (std::shared_ptr<pqxx::connection> );
    ~IndexQueueDAO ();

    std::deque<Document> getQueue () override;

    void saveQueue (std::deque<Document>& ) override;

    void setConn (const std::shared_ptr<pqxx::connection> &conn) {
        IndexQueueDAO::conn = conn;
    }
};


#endif //CRAWLER_INDEXQUEUEDAOIMPL_H
