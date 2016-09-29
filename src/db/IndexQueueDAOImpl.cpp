//
// Created by user on 8/16/16.
//

#include <utility>

#include "IndexQueueDAOImpl.h"

using namespace std;
using namespace pqxx;

IndexQueueDAOImpl::IndexQueueDAOImpl ()
    // TODO: exception handling
    : conn (make_shared<connection> ("dbname=index user=postgres"))
{}

IndexQueueDAOImpl::IndexQueueDAOImpl (shared_ptr<connection> newConn)
    : conn (newConn)
{}

IndexQueueDAOImpl::~IndexQueueDAOImpl () {}

deque<string> IndexQueueDAOImpl::getQueue () {
    work w (*this->conn);

    // TODO: error handling
    auto result = w.exec (
            "SELECT * FROM indexQueue;"
    );

    w.commit ();

    deque<string> queue;

    for (auto const & r : result) {
        queue.push_back (r[0].as<char const*> ());
    }

    return queue;
}

void IndexQueueDAOImpl::saveQueue (std::deque<std::string> &) {

}
