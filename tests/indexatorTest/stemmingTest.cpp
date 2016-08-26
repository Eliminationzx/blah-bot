//
// Created by user on 7/26/16.
//

#include <array>
#include <string>

#include <gmock/gmock.h>

#include <index/Worker.h>
#include <index/Stemmer.h>

using namespace std;

TEST (indexator, shouldStemTokens) {
    Worker i;


}

TEST (stemmer, test1) {
    Stemmer s;
    string caresses = "caresses";
    string ponies = "ponies";
    string ties = "ties";
    string caress = "caress";
    string cats = "cats";
    string blah = "blah";
    string vasya = "vasya";

//    ASSERT_STREQ (s.step1 (caresses).data (), "caress");
//    ASSERT_STREQ (s.step1 (ponies).data (), "poni");
//    ASSERT_STREQ (s.step1 (ties).data (), "ti");
//    ASSERT_STREQ (s.step1 (caress).data (), "caress");
//    ASSERT_STREQ (s.step1 (cats).data (), "cat");
//    ASSERT_STREQ (s.step1 (blah).data (), "blah");
//    ASSERT_STREQ (s.step1 (vasya).data (), "vasya");

    string feed = "feed";
    string agreed = "agreed";
    string plastered = "plastered";
    string bled = "bled";
    string motoring = "motoring";
    string sing = "sing";
    string conflat = "conflat";
    string troubl = "troubl";
    string siz = "siz";
    string hopp = "hopp";
    string tann = "tann";
    string fizz = "fizz";
    string hiss = "hiss";
    string fail = "fail";
    string fil = "fil";

//    ASSERT_STREQ (s.step1 (feed).data (), "feed");
    ASSERT_STREQ (s.step1 (agreed).data (), "agree");
    ASSERT_STREQ (s.step1 (plastered).data (), "plaster");
    ASSERT_STREQ (s.step1 (bled).data (), "bled");
    ASSERT_STREQ (s.step1 (motoring).data (), "motor");
    ASSERT_STREQ (s.step1 (sing).data (), "sing");
    ASSERT_STREQ (s.step1 (conflat).data (), "conflate");
    ASSERT_STREQ (s.step1 (troubl).data (), "touble");
    ASSERT_STREQ (s.step1 (siz).data (), "siz");
    ASSERT_STREQ (s.step1 (hopp).data (), "hop");
    ASSERT_STREQ (s.step1 (tann).data (), "tan");
    ASSERT_STREQ (s.step1 (fizz).data (), "fizz");
    ASSERT_STREQ (s.step1 (hiss).data (), "hiss");
    ASSERT_STREQ (s.step1 (fail).data (), "fail");
    ASSERT_STREQ (s.step1 (fil).data (), "file");
}

TEST (stemmer, test1c) {
    Stemmer s;
    string happy = "happy";
    string sky = "sky";

    ASSERT_STREQ (s.step1c (happy).data (), "happi");
    ASSERT_STREQ (s.step1c (sky).data (), "sky");
}
