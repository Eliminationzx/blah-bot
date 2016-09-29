//
// Created by user on 7/24/16.
//

#ifndef CRAWLER_ROBOTSTXTTABLE_H
#define CRAWLER_ROBOTSTXTTABLE_H

#include <string>
#include <vector>

#include <pqxx/pqxx>

class RobotstxtDb {
    pqxx::connection* conn;

public:
    RobotstxtDb ();
    virtual ~RobotstxtDb();

    /*!
     * \brief is robots.txt in the db
     * @param url address of the web site
     * @return true if the data from robots.txt file of the site is in db
     */
    virtual bool isInDb (const std::string& url) const;

    /*!
     * \brief insert robots.txt rules into the db
     * @param rules array of robots.txt rules
     */
    virtual void insertRules (std::vector<std::string>& rules, int siteId) const;

    virtual int insertRobotstxt (const std::string& address, bool siteDisallowed) const;

    /*!
     * \brief is a page is disallowed
     * @param url address of the page
     * @return boolean value
     */
    virtual bool isPageDisallowed (std::string& url) const;
};


#endif //CRAWLER_ROBOTSTXTTABLE_H
