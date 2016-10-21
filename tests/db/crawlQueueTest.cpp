//
// Created by ololosh on 10/6/16.
//

#include <string>

#include <gmock/gmock.h>
#include <pqxx/pqxx>

#include "db/CrawlerQueueDAO.h"

using namespace std;
using namespace pqxx;


TEST (crawlerQueue, shouldLoadQueue) {
    CrawlerQueueDAO crawlerQueueDAO (
            make_shared<connection> ("dbname=index user=postgres")
    );
    string expectedAddress = "https://en.wikipedia.org";

    auto queue = crawlerQueueDAO.loadQueue ();

    auto address = queue.front ().getAddress ();

    ASSERT_EQ (address, expectedAddress);
}
