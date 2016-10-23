//
// Created by ololosh on 9/30/16.
//

#include <memory>
#include <string>
#include <deque>

#include <gmock/gmock.h>
#include <pqxx/pqxx>

#include "db/IndexQueueDAO.h"
#include "index/Document.h"
#include "parser/HTMLDocumentParser.h"

using namespace std;
using namespace pqxx;

TEST (IndexQueueDAO, storeAndLoadQueue) {
    IndexQueueDAO indexQueueDAO (
        make_shared<connection> ("user=postgres dbname=index_test")
    );
    deque<Document> sourceQueue;
    Document tmp (make_shared<HTMLDocumentParser> ());
    tmp.setAddress ("page 1");
    tmp.setHtml ("html code for page 1");
    sourceQueue.push_back (tmp);

    indexQueueDAO.saveQueue (sourceQueue);

    auto queue = indexQueueDAO.getQueue ();
    auto doc = queue.front ();

    ASSERT_EQ (doc.getAddress (), tmp.getAddress ());
    ASSERT_EQ (doc.getHtml (), tmp.getHtml ());
}
