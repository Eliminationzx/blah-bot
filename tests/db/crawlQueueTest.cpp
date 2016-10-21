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
    string expectedAddress ("https://en.wikpedia.org/wiki/Main_Page");

    auto queue = crawlerQueueDAO.loadQueue ();

    ASSERT_EQ (queue.front ().getAddress (), expectedAddress);
}
