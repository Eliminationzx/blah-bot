//
// Created by user on 8/12/16.
//

#include <cstring>

#include "Stemmer.h"

using namespace std;

vector<string>& Stemmer::stem (std::vector<std::string>& tokens) const {
    return tokens;
}

bool Stemmer::isConsonant (char c) const {
    return !this->isVowel (c);
}

bool Stemmer::isVowel (char c) const {
    switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
    }
}

unsigned int Stemmer::measure (std::string word) const {
    uint32_t measure = 0;
    uint32_t i = 0;

    while (true) {
        if (i > this->endPos)
            return measure;

        if (this->isVowel (word[i]))
            break;

        i++;
    }

    i++;

    while (true) {
        while (true) {
            if (i >= this->endPos)
                return measure;

            if (this->isConsonant (word[i]))
                break;

            i++;
        }

        i++;
        measure++;

        while (true) {
            if (i >= this->endPos)
                return measure;

            if (this->isVowel (word[i]))
                break;

            i++;
        }

        i++;
    }
}

bool Stemmer::vowelInStem (std::string& str) const {
    for (uint64_t i = 0; i < this->endPos; ++i)
        if (isVowel (str[i]))
            return true;

    return false;
}

bool Stemmer::cvc (string& str) const {
    auto last = str.length () - 1;

    if (isVowel (str[last]) || isConsonant (str[last - 1]) || isVowel (str[last - 2]))
        return false;

    auto ch = str.back ();

    if (ch == 'w' || ch == 'x' || ch == 'y')
        return false;

    return true;
}

bool Stemmer::doubleConsonant (string& str) const {
    auto len = str.length ();

    if (str[len - 1] != str[len - 2])
        return false;

    return isConsonant (str.back ());
}

bool Stemmer::endsWith (std::string& str, char const* suf) {
    auto len = strlen (suf);

    if (str.length () < len)
        return false;

    if (str.rfind (suf) == (str.length () - len)) {
        endPos = str.length () - len;

        return true;
    }
}

string& Stemmer::step1 (string& str) {
    auto strlast = str.length () - 1;

    if (str.back () == 's') {
        if (endsWith (str, "sses"))
            str.erase (strlast - 1);
        else if (endsWith (str, "ies"))
            str.erase (strlast - 1);
        else if (str[strlast - 1] != 's')
            str.erase (strlast);
    }

    if (endsWith (str, "eed")) {
        if (measure (str) > 0)
            str.pop_back ();
    } else if ((endsWith (str, "ed") || endsWith (str, "ing")) && vowelInStem (str)) {
        if (endsWith (str, "ed"))
            str.erase (strlast - 1);
        else if (endsWith (str, "ing"))
            str.erase (strlast - 2);

        if (endsWith (str, "at") || endsWith (str, "bl") || endsWith (str, "iz"))
            str.push_back ('e');
        else if (doubleConsonant (str)) {
            auto ch = str.back ();

            if (ch != 's' && ch != 'z' && ch != 'l')
                str.pop_back ();
        } else if (measure (str) == 1 && cvc (str))
            str.push_back ('e');
    }


    return str;
}

string& Stemmer::step1c (string& str) {
    if (endsWith (str, "y") && vowelInStem (str))
        str.back () = 'i';

    return str;
}

string& Stemmer::step2 (string& str) {
    return str;
}

string& Stemmer::step3 (string& str) {
    return str;
}

string& Stemmer::step4 (string& str) {
    return str;
}

string& Stemmer::step5 (string& str) {
    return str;
}

string& Stemmer::step6 (string& str) {
    return str;
}
