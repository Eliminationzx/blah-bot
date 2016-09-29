#include <pqxx/pqxx>

#include "robotscontroller.h"

using namespace std;
using namespace pqxx;

namespace web
{
    RobotsController::RobotsController(shared_ptr<HTTP> _http, shared_ptr<RobotstxtDb> _db)
        : http (_http), db (_db)
    {
    //    this->logger->set_level (spdlog::level::debug);
    }

    bool RobotsController::allowed (string &url) const
    {
    //    this->logger->debug (__PRETTY_FUNCTION__);

        auto domainName = this->parseDomainName (url);
        auto robotsPath = domainName.back () == '/' ?
                          domainName + "robots.txt" :
                          domainName + "/robots.txt";

        if (!this->db->isInDb (domainName)) {
            auto robotstxt = this->http->get (robotsPath);

            if (robotstxt.empty ())
                return true;

            auto rules = this->parseRobotsTxt (robotstxt);
            bool siteDisallowed = false;

            if (rules.empty ())
                return true;

            if (rules[0] == "*")
                siteDisallowed = true;

            auto siteId = this->db->insertRobotstxt (domainName, siteDisallowed);

            this->db->insertRules (rules, siteId);
        }

        return !this->db->isPageDisallowed (url);
    }

    string RobotsController::parseDomainName (string &url) const {
        return url.substr (0, url.find ("/", 10));
    }

    vector<string> RobotsController::parseRobotsTxt(std::string contents) const {
        stringstream ss (contents);
        string line;
        vector<string> rules;

        bool userAgentFound = false;

        while (getline (ss, line, '\n')) {
            if (line[0] == '#')
                continue;

            if ((line[0] == ' ' || line.empty ()) && !userAgentFound)
                continue;

            if (line[0] == 'U') {
                if (this->checkUserAgent (line)) {
                    userAgentFound = true;
                } else {
                    if (userAgentFound)
                        userAgentFound = false;

                    continue;
                }
            }

            if (line[0] == 'D') {
                if (userAgentFound) {
                    auto value = this->getValue (line);

                    rules.push_back (value);

                    if (value == string ("/"))
                        break;
                }
            }
        }

        return rules;
    }

    bool RobotsController::checkUserAgent (string& line) const
    {
    //    auto uaPos = line.find (':') + 1;

        return this->userAgent == &line[12] || &line[12] == "*";
    }

    string RobotsController::getValue (string& line) const
    {
    //    auto valuePos = line.find (':') + 1;

        return &line[10];
    }

} //namespace web
