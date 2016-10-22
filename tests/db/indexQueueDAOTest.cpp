//
// Created by ololosh on 9/30/16.
//

#include <memory>
#include <string>

#include <gmock/gmock.h>
#include <pqxx/pqxx>

#include "db/IndexQueueDAO.h"

using namespace std;
using namespace pqxx;

TEST (IndexQueueDAO, storeAndLoadQueue) {
    IndexQueueDAO indexQueueDAO (
        make_shared<connection> ("user=postgres dbname=index_test")
    );

}
