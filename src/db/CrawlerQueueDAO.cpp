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

deque<string> CrawlerQueueDAO::loadQueue () {
    work w (*conn);

    auto result = w.exec (
            "SELECT * FROM crawlerqueue;"
    );
    w.commit ();

    deque<string> queue;

    for (auto const& r : result) {
        queue.push_back (r[0].as<char const*> ());
    }

    return queue;
}

void CrawlerQueueDAO::storeQueue (const std::deque<string>& queue) {
    conn->prepare ("insert", "INSERT INTO crawlerqueue VALUES ($1)");
    work w (*conn);

    for (const auto& url : queue) {
        w.prepared ("insert") (url).exec ();
    }

    w.commit ();
}

