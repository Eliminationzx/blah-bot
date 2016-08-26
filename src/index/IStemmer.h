//
// Created by user on 8/15/16.
//

#ifndef CRAWLER_ISTEMMER_H
#define CRAWLER_ISTEMMER_H

#include <string>
#include <vector>

class IStemmer {
    virtual std::vector<std::string>& stem (std::vector<std::string>& ) const = 0;
};


#endif //CRAWLER_ISTEMMER_H
