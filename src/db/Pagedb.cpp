//
// Created by user on 8/17/16.
//

#include "Pagedb.h"

using namespace std;
using namespace pqxx;

Pagedb::Pagedb ()
        : conn (make_shared<connection> ("dbname=index user=postgres"))
{}

Pagedb::Pagedb (shared_ptr<connection> newConn)
        : conn (newConn)
{}

Pagedb::~Pagedb () {}

#include <iostream>

void Pagedb::saveURL (Page& page) {
    work w (*conn);

    cout << __PRETTY_FUNCTION__ << '\n' << "trying to select\n";

//    auto result = w.exec (
//            "SELECT * FROM insertorselectid (" + w.quote (page.address) + ");"
//    );
    auto result = w.exec (
            "SELECT id FROM document WHERE url=" + w.quote (page.address) + ";"
    );

    if (result[0][0].size () == 0) {
        result = w.exec (
                "INSERT INTO document (url, lasttimeindexed) values (" +
                        w.quote (page.address) + ", CURRENT_DATE)"
                "RETURNING id;"
        );
    }

    w.commit ();

    page.id = result[0][0].as<unsigned int> ();
}
