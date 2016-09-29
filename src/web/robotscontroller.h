#ifndef ROBOTSCONTROLLER_H
#define ROBOTSCONTROLLER_H

#include <string>
#include <memory>

#include <spdlog/spdlog.h>

#include "http.h"
#include "db/robotstxtDb.h"

namespace web
{
    /*!
     * \brief The RobotsController class
     *
     * Performs operations on a robots.txt file (loading, parsing, saving to the db).
     * Checks if a page is allowed to access to.
     */
    class RobotsController
    {
    //    std::shared_ptr<spdlog::logger> logger = spdlog::basic_logger_mt (
    //            "RobotsController",
    //            "../../../../log/crawler.log"
    //    );
        std::shared_ptr<HTTP> http;
        std::shared_ptr<RobotstxtDb> db;
        std::string userAgent = "blah-bot";

    public:
        RobotsController(std::shared_ptr<HTTP>, std::shared_ptr<RobotstxtDb>);

        /*!
         * \brief Is page allowed.
         * \param url A page to be checked
         * \return true if the page is allowed to connect to, false otherwise
         *
         * Checks rules for a page in the db.
         * If there's no robots.txt for given site in the db -
         * download, parse it and add rules to the db.
         */
        bool allowed (std::string& url) const;

    private:
        /*!
         * \brief parseDomainName
         * \param url An addres of a page
         * \return Domain name of a site
         */
        std::string parseDomainName (std::string& url) const;

        /*!
         * \brief Parse robots.txt
         * @param contents
         * @return array of disallowed pages from the web site
         */
        std::vector<std::string> parseRobotsTxt (std::string contents) const;

        bool checkUserAgent (std::string& line) const;
        std::string getValue (std::string& line) const;
    };
} // web namespace

#endif // ROBOTSCONTROLLER_H
