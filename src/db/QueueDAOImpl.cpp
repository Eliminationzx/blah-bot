//
// Created by user on 8/16/16.
//

#include <utility>

#include "QueueDAOImpl.h"

using namespace std;
using namespace pqxx;

QueueDAOImpl::QueueDAOImpl ()
    // TODO: exception handling
    : conn (make_shared<connection> ("dbname=index user=postgres"))
{}

QueueDAOImpl::QueueDAOImpl (shared_ptr<connection> newConn)
    : conn (newConn)
{}

QueueDAOImpl::~QueueDAOImpl () {}

deque<string> QueueDAOImpl::getQueue () {
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

void QueueDAOImpl::saveQueue (std::deque<std::string> &) {

}
