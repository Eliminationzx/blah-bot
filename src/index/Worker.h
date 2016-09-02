//
// Created by user on 7/26/16.
//

#ifndef CRAWLER_INDEXATOR_H
#define CRAWLER_INDEXATOR_H

#include <vector>
#include <string>
#include <memory>

#include <spdlog/spdlog.h>

#include <index/Document.h>

/*!
 * Manages indexing loop
 */
class Worker {
    std::shared_ptr<spdlog::logger> logger = spdlog::basic_logger_st (
            "worker",
            "/home/ololosh/pj/cpp/se/indexer/log/worker.log"
    );

public:
    Worker ();
    ~Worker ();

    Worker (Worker& ) = delete;
    Worker& operator = (const Worker& ) = delete;
    Worker (Worker&& ) = default;
    Worker& operator = (Worker&& ) = default;

    /*!
     * \brief start indexing a web page
     *
     * Starts indexing loop:
     * read a html file from the source dir,
     * parse it, tokenize, stemm and add to index.
     */
    void start () const;

    /*!
     * \brief split text into a list of tokens
     * @param text to tokenize
     * @returns a vector of tokens
     *
     * Teporary implementation: split words by all non alphanumeric characters
     */
    std::vector<std::string> tokenize (std::string& ) const;

    /*!
     * Tokens stemming.
     * @param list of tokens
     * @returns list of stemmed tokens
     *
     * Porter`s algorithm
     */
    std::vector<std::string>& stem (std::vector<std::string>&) const;

private:
};


#endif //CRAWLER_INDEXATOR_H
