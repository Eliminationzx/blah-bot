//
// Created by user on 8/12/16.
//

#ifndef CRAWLER_STEMMER_H
#define CRAWLER_STEMMER_H

#include <string>
#include <vector>

#include "IStemmer.h"

/*!
 * Porter`s stemming algorithm
 */
class Stemmer : public IStemmer {
    uint64_t endPos = 0;

public:
    std::vector<std::string>& stem (std::vector<std::string>& ) const override;

    unsigned int measure (std::string word) const;

private:
    bool vowelInStem (std::string& str) const;

    bool isConsonant (char c) const;
    bool isVowel (char c) const;
    bool endsWith (std::string& str, char const* suf);
    bool doubleConsonant (std::string& str) const;
    bool cvc (std::string& str) const;

public:
    std::string& step1 (std::string& );
    std::string& step1c (std::string& );
    std::string& step2 (std::string& );
    std::string& step3 (std::string& );
    std::string& step4 (std::string& );
    std::string& step5 (std::string& );
    std::string& step6 (std::string& );
};


#endif //CRAWLER_STEMMER_H
