//
// Created by ololosh on 10/4/16.
//

#include "CrawlerQueueDAO.h"

using namespace std;
using namespace pqxx;

CrawlerQueueDAO::CrawlerQueueDAO (std::shared_ptr<pqxx::connection> c)
    : conn (c)
{}

#include <iostream>

deque<Document> CrawlerQueueDAO::loadQueue () {
    work w (*conn);

    auto result = w.exec (
            "SELECT * FROM crawlerqueue;"
    );
    w.commit ();

    deque<Document> queue;
    Document tmpDoc (make_shared<HTMLDocumentParser> ());

    for (auto const& r : result) {
        tmpDoc.setAddress (r[0].as<char const*> ());

        queue.push_back (tmpDoc);
    }

    return queue;
}

void CrawlerQueueDAO::storeQueue (const std::deque<Document>& queue) {

}

