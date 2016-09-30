//
// Created by ololosh on 9/30/16.
//

#include <memory>

#include <gmock/gmock.h>
#include <pqxx/pqxx>

#include "db/QueueDAOImpl.h"

using namespace std;

TEST (crawlerQueue, shouldGetTheQueue) {
    auto conn = make_shared<pqxx::connection> ("dbname=index user=postgres");
    QueueDAOImpl crawlerQueueDb (conn, "crawlerqueue");
    deque<string> expectedQueue {
            "https://en.wikipedia.org"
    };

    EXPECT_THAT (crawlerQueueDb.getQueue (), ::testing::ContainerEq (expectedQueue));
}

TEST (indexQueue, shouldGetTheQueue) {
    auto conn = make_shared<pqxx::connection> ("dbname=index user=postgres");
    QueueDAOImpl crawlerQueueDb (conn, "indexqueue");
    deque<string> expectedQueue {
            "https://en.wikipedia.org"
    };

    EXPECT_THAT (crawlerQueueDb.getQueue (), ::testing::ContainerEq (expectedQueue));
}