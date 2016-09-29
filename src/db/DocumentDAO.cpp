//
// Created by ololosh on 9/4/16.
//

#include "DocumentDAO.h"

using namespace std;
using namespace pqxx;

DocumentDAO::DocumentDAO ()
    : conn (make_shared<connection> ("dbname=index user=postgres"))
{}

DocumentDAO::DocumentDAO (shared_ptr<connection> ptr)
    : conn (ptr)
{}

string DocumentDAO::getUrlById (uint64_t id) const {
    work w (*conn);

    auto res = w.exec (
        "SELECT url FROM document WHERE id=" + w.quote (id) + ";"
    );

    w.commit ();

    // TODO: error handling

    if (res[0][0].size () != 0) {
        return res[0][0].as<char const*> ();
    }

    return "";
}
