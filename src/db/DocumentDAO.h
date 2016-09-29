//
// Created by ololosh on 9/4/16.
//

#ifndef INDEXER_DOCUMENTDAO_H
#define INDEXER_DOCUMENTDAO_H

#include <memory>

#include <pqxx/pqxx>


class DocumentDAO {
    std::shared_ptr<pqxx::connection> conn;

public:
    DocumentDAO ();
    DocumentDAO (std::shared_ptr<pqxx::connection> );
    ~DocumentDAO () = default;

    std::string getUrlById (uint64_t ) const;

};


#endif //INDEXER_DOCUMENTDAO_H
