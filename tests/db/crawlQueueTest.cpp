//
// Created by ololosh on 10/6/16.
//

#include <string>
#include <deque>

#include <gmock/gmock.h>
#include <pqxx/pqxx>

#include "db/CrawlerQueueDAO.h"

using namespace std;
using namespace pqxx;

TEST (crawlerQueue, shouldStoreQueue) {
    CrawlerQueueDAO crawlerQueueDAO (
            make_shared<connection> ("dbname=index_test user=postgres")
    );
    deque<string> sourceQueue {
            "page 1",
            "page 2",
            "page 3"
    };

    crawlerQueueDAO.storeQueue (sourceQueue);

    auto queue = crawlerQueueDAO.loadQueue ();

    EXPECT_THAT (queue, ::testing::ContainerEq (sourceQueue));
}