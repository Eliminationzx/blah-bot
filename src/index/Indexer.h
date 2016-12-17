//
// Created by user on 7/26/16.
//

#ifndef CRAWLER_INDEXATOR_H
#define CRAWLER_INDEXATOR_H

#include <vector>
#include <string>
#include <memory>
#include <deque>

#include <spdlog/spdlog.h>

#include "index/Document.h"
#include "db/IndexWriter.h"

/*!
 * Manages indexing loop
 */
class Indexer {
    uint64_t id;
    std::shared_ptr<std::mutex> indexingQueueMutex;
    std::shared_ptr<std::deque<Document>> indexingQueue;
    std::shared_ptr <IndexWriter> indexWriter;
    std::shared_ptr<spdlog::logger> logger = spdlog::basic_logger_st (
            "worker",
            "/home/ololosh/pj/cpp/se/indexer/log/worker.log"
    );
    bool running = false;

public:
    Indexer (uint64_t);
    ~Indexer ();

    Indexer (Indexer& ) = delete;
    Indexer& operator = (const Indexer& ) = delete;
    Indexer (Indexer&& ) = default;
    Indexer& operator = (Indexer&& ) = default;

    void setIndexingQueue (std::shared_ptr<std::deque<Document>> );

    void setIndexingQueueMutex (std::shared_ptr<std::mutex> );

    void setIndexWriter (std::shared_ptr <IndexWriter> );

    void operator () ();

    /*!
     * \brief start indexing a web page
     *
     * Starts indexing loop:
     * read a html file from the source dir,
     * parse it, tokenize, stemm and add to index.
     */
    void start ();

    /*!
     * \brief split text into a list of tokens
     * @param text to tokenize
     * @returns a vector of tokens
     *
     * Teporary implementation: split words by all non alphanumeric characters
     */
    std::vector<std::string> tokenize (const std::string& );
private:
};


#endif //CRAWLER_INDEXATOR_H
