//
// Created by user on 8/16/16.
//

#include <utility>
#include <cstring>

#include "IndexQueueDAO.h"
#include "parser/HTMLDocumentParser.h"

using namespace std;
using namespace pqxx;

IndexQueueDAO::IndexQueueDAO ()
    // TODO: exception handling
    : conn (make_shared<connection> ("dbname=index user=postgres"))
{}

IndexQueueDAO::IndexQueueDAO (shared_ptr<connection> newConn)
    : conn (newConn)
{}

IndexQueueDAO::~IndexQueueDAO () {}

deque<Document> IndexQueueDAO::getQueue () {
    work w (*this->conn);

    // TODO: error handling
    auto result = w.exec (
            "SELECT * FROM indexqueue;"
    );

    w.commit ();

    deque<Document> queue;
    Document tmpDoc (make_shared<HTMLDocumentParser> ());

    for (auto const & r : result) {
        tmpDoc.setAddress (r[0].as<char const*> ());
        tmpDoc.setHtml (r[1].as<char const*> ());

        queue.push_back (tmpDoc);
    }

    return queue;
}

void IndexQueueDAO::saveQueue (std::deque<Document>& queue) {
    conn->prepare ("insertCrawlerQueue", "INSERT INTO indexqueue VALUES ($1, $2);");
    work w (*conn);

    for (const auto& item : queue) {
        w.prepared ("insertCrawlerQueue") (item.getAddress (), item.getHtml ()).exec ();
    }

    w.commit ();
}
