//
// Created by user on 7/26/16.
//

#ifndef CRAWLER_PAGE_H
#define CRAWLER_PAGE_H

#include <string>
#include <vector>
#include <utility>

/*!
 * \brief Page data struct
 *
 * Stores all the needed information about a web page,
 */
struct Page {
    unsigned int id;
    std::string address;
    bool status = true;
    std::string html;
    std::string text;
    std::vector<std::string> links;

    Page () {}
    Page (const Page& another) {
        this->id = another.id;
        this->address = another.address;
        this->status = another.status;
        this->html = another.html;
        this->text = another.text;
        this->links = another.links;
    }
    Page (Page&& another)
        : address (std::move (another.address)),
          html (std::move (another.html)),
          text (std::move (another.text)),
          links (std::move (another.links))
    {
        this->id = another.id;
        another.id = 0;
        this->status = another.status;
        another.status = false;
    }
};

#endif //CRAWLER_PAGE_H
