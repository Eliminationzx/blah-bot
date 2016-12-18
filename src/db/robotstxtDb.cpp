//
// Created by user on 7/24/16.
//

#include "robotstxtDb.h"

using namespace std;
using namespace pqxx;

RobotstxtDb::RobotstxtDb() {
    this->conn = new connection ("dbname=index_test user=postgres");
}

RobotstxtDb::~RobotstxtDb() {
    delete this->conn;
}

bool RobotstxtDb::isInDb(const std::string &url) const {
    work w (*this->conn);
    auto sitesResult = w.exec (
            "SELECT EXISTS("
                    "SELECT 1 FROM sites WHERE address=" + w.quote (url) +
            ");"
    );

    w.commit ();

    return sitesResult[0][0].as<bool> ();
}

int RobotstxtDb::insertRobotstxt (const std::string& address, bool siteDisallowed) const {
    work w (*this->conn);
    auto result = w.exec (
            "INSERT INTO sites (address, isallblocked, lastupdate) "
            "VALUES (" + w.quote (address) + ", " +
                    w.quote (siteDisallowed) +
                    ", 2016-07-25) "
            "RETURNING id;"
    );

    w.commit ();

    return result[0][0].as<int> ();
}

void RobotstxtDb::insertRules(std::vector<std::string> &rules, int siteId) const {

}

bool RobotstxtDb::isPageDisallowed(std::string &url) const {
    // should check in sites table if all pages are disallowed

    work w (*this->conn);
    auto pageResult = w.exec (
            "SELECT EXISTS("
                    "SELECT 1 FROM disallowedPages WHERE address=" + w.quote (url) +
            ");"
    );

    w.commit ();

    return pageResult[0][0].as<bool> ();
}