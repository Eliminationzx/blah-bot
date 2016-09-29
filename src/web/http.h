#ifndef HTTP_H
#define HTTP_H

#include <string>

#include <curl/curl.h>

namespace web
{
/*!
* \brief The HTTP class
*
* Manages HTTP connections
*/
class HTTP
{
    CURL* curl;

public:
    HTTP() noexcept;
    virtual ~HTTP () noexcept;

    /*!
     * \brief get
     *
     * Given a address, sends a GET request to it and loads the data.
     *
     * \param url An address of a web page
     * \return HTML code of the page
     */
    virtual std::string get (std::string& url) const;

};
} // web namespace

#endif // HTTP_H
