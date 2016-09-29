#include <regex>

#include "http.h"

using namespace std;

namespace web
{
    HTTP::HTTP() noexcept
    {
        this->curl = curl_easy_init ();
    }

    HTTP::~HTTP() noexcept {
        curl_easy_cleanup (this->curl);
    }

    size_t writeCallback (char* ptr, size_t size, size_t mmeb, string* userdata) {
        userdata->append (ptr);

        return size * mmeb;
    }

    string HTTP::get (string &url) const
    {
        string res;

        curl_easy_setopt (curl, CURLOPT_URL, url.data ());
        curl_easy_setopt (curl, CURLOPT_WRITEDATA, &res);
        curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, writeCallback);

        curl_easy_perform (curl);

        return res;
    }

} // web namespace
