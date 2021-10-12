// Rioki's Standard Extentions
// Copyright 2020-2021 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <stdex/algorithm.h>

TEST(algorithm, equals_equal) 
{
    auto lst = std::list<int>{0, 1, 2, 3, 4, 5};
    auto vec = std::vector<int>{0, 1, 2, 3, 4, 5};
    EXPECT_TRUE(stdex::equals(begin(lst), end(lst), begin(vec), end(vec)));
}

TEST(algorithm, equals_not_equal) 
{
    auto lst = std::list<int>{0, 1, 2, 3, 4, 5};
    auto vec = std::vector<int>{0, 1, 2, 99, 4, 5};
    EXPECT_FALSE(stdex::equals(begin(lst), end(lst), begin(vec), end(vec)));
}

TEST(algorithm, equals_shorter) 
{
    auto lst = std::list<int>{0, 1, 2, 3, 4, 5};
    auto vec = std::vector<int>{0, 1, 2, 3, 4};
    EXPECT_FALSE(stdex::equals(begin(lst), end(lst), begin(vec), end(vec)));
}

TEST(algorithm, equals_longer) 
{
    auto lst = std::list<int>{0, 1, 2, 3, 4, 5};
    auto vec = std::vector<int>{0, 1, 2, 3, 4, 5, 6};
    EXPECT_FALSE(stdex::equals(begin(lst), end(lst), begin(vec), end(vec)));
}