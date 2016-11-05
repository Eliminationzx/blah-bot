//
// Created by user on 7/26/16.
//

#include <array>
#include <string>

#include <gmock/gmock.h>

#include <index/Stemmer.h>

using namespace std;

TEST (stemmer, test1) {
    int wordsNum = 8;
    string words[wordsNum] {
        "caresses",
        "ponies",
        "ties",
        "cats",
        "revival",
        "allowance",
        "inference",
        "adjustable"
    };
    string newWords[wordsNum] {
        "caress",
        "poni",
        "ti",
        "cat",
        "reviv",
        "allow",
        "infer",
        "adjust"
    };
    size_t newEnd = 0;

    for (int i = 0; i < wordsNum; ++i)
    {
        newEnd = stem (const_cast<char*> (words[i].data ()), 0, words[i].size () - 1);

        ASSERT_EQ (newWords[i], string (words[i], 0, newEnd + 1));
    }
}

