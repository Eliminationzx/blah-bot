//
// Created by user on 8/17/16.
//

#ifndef CRAWLER_PAGEDB_H
#define CRAWLER_PAGEDB_H

#include <memory>

#include <pqxx/pqxx>

#include "PageDAO.h"

class Pagedb : public PageDAO {
    std::shared_ptr<pqxx::connection> conn;

public:
    Pagedb ();
    Pagedb (std::shared_ptr<pqxx::connection> );
    ~Pagedb ();

    /*!
     * \brief Save page address to the db.
     * @param Page object reference
     *
     * Try to save the address to the db.
     * Page's id field is set to the id from the db.
     */
    void saveURL (Page& ) override;
};


#endif //CRAWLER_PAGEDB_H
