//
// Created by user on 12/15/16.
//

#ifndef INDEXER_INDEXWRITER_H
#define INDEXER_INDEXWRITER_H

#include <memory>

#include <pqxx/pqxx>

#include "index/Document.h"

class IndexWriter {
    std::shared_ptr <pqxx::connection> conn;

public:
    IndexWriter () = delete;
    IndexWriter (std::shared_ptr <pqxx::connection> );

    void write (Document& doc);
};


#endif //INDEXER_INDEXWRITER_H
