//
// Created by ololosh on 11/10/16.
//

#include <string>
#include <iostream>

#include "gmock/gmock.h"

#include "config/Config.h"

TEST (configTest, setAndGetMethods)
{
    Config conf;
    bool b = true;
    int i = 100500;
    double d = 100.500;
    std::string s = "100500";

    conf.setBool ("bool", b);
    conf.setInt ("int", i);
    conf.setDouble ("double", d);
    conf.setString ("string", s);

    ASSERT_EQ (b, conf.getBool ("bool"));
    ASSERT_EQ (i, conf.getInt ("int"));
    ASSERT_EQ (d, conf.getDouble ("double"));
    ASSERT_EQ (s, conf.getString ("string"));
//    ASSERT_EQ (s, conf.getString ("vasya"));
}

TEST (configTest, loadMethod)
{
    Config conf2;
    bool b = true;
    int i = 100500;
    double d = 100.500;
    std::string s = "100500";

    std::cout << "\nblah blah blah\n";

    conf2.loadFrom ("./conf");

    ASSERT_EQ (b, conf2.getBool ("bool"));
    ASSERT_EQ (i, conf2.getInt ("int"));
    ASSERT_EQ (d, conf2.getDouble ("double"));
    ASSERT_EQ (s, conf2.getString ("string"));
}
