// Rioki's Standard Extentions
// Copyright 2020-2021 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.

#include <gtest/gtest.h>
#include <tuple>
#include <stdex/ring.h>
#include <stdex/algorithm.h>

TEST(ring, default_contructor)
{
    auto r = stdex::ring<int, 10>();
    EXPECT_TRUE(r.empty());
    EXPECT_EQ(0u, r.size());
    EXPECT_EQ(10u, r.capacity());
}

TEST(ring, fill_forward)
{
    auto r = stdex::ring<int, 10>();
    for (unsigned i = 0u; i < r.capacity(); i++)
    {
        r.push_back(i);
    }
    EXPECT_EQ(10u, r.size());
    EXPECT_EQ(10u, r.capacity());
    EXPECT_EQ(0u, r.front());
    EXPECT_EQ(9u, r.back());

    auto ref = 0u;
    for (const auto& v : r)
    {
        EXPECT_EQ(ref, v);
        ref++;
    }
    EXPECT_EQ(10u, ref);
}

TEST(ring, fill_backward)
{
    auto r = stdex::ring<int, 10>();
    for (unsigned i = 0u; i < r.capacity(); i++)
    {
        r.push_front(i);
    }
    EXPECT_EQ(10u, r.size());
    EXPECT_EQ(10u, r.capacity());
    EXPECT_EQ(9u, r.front());
    EXPECT_EQ(0u, r.back());

    auto ref = 9u;
    for (const auto& v : r)
    {
        EXPECT_EQ(ref, v);
        ref--;
    }
    EXPECT_EQ(-1, ref);
}

TEST(ring, roll_over_forward)
{
    auto r = stdex::ring<int, 10>();
    for (unsigned i = 0u; i < r.capacity() * 2; i++)
    {
        r.push_back(i);
    }
    EXPECT_EQ(10u, r.size());
    EXPECT_EQ(10u, r.front());
    EXPECT_EQ(19u, r.back());

    auto ref = 10u;
    for (const auto& v : r)
    {
        EXPECT_EQ(ref, v);
        ref++;
    }
    EXPECT_EQ(20u, ref);
}

TEST(ring, roll_over_backward)
{
    auto r = stdex::ring<int, 10>();
    for (unsigned i = 0u; i < r.capacity() * 2; i++)
    {
        r.push_front(i);
    }
    EXPECT_EQ(10u, r.size());
    EXPECT_EQ(19u, r.front());
    EXPECT_EQ(10u, r.back());

    auto ref = 19u;
    for (const auto& v : r)
    {
        EXPECT_EQ(ref, v);
        ref--;
    }
    EXPECT_EQ(9u, ref);
}

TEST(ring, init_args)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    EXPECT_EQ(10u, rng.size());
    EXPECT_EQ(10u, rng.capacity());
    EXPECT_EQ(0u, rng.front());
    EXPECT_EQ(9u, rng.back());

    auto ref = 0u;
    for (const auto& v : rng)
    {
        EXPECT_EQ(ref, v);
        ref++;
    }
    EXPECT_EQ(10u, ref);
}

TEST(ring, init_args_to_many)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    EXPECT_EQ(10u, rng.size());
    EXPECT_EQ(10u, rng.capacity());
    EXPECT_EQ(0u, rng.front());
    EXPECT_EQ(9u, rng.back());

    auto ref = 0u;
    for (const auto& v : rng)
    {
        EXPECT_EQ(ref, v);
        ref++;
    }
    EXPECT_EQ(10u, ref);
}

TEST(ring, init_same_container)
{
    auto cont = std::deque<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto rng = stdex::ring<int, 10>(cont);

    EXPECT_EQ(10u, rng.size());
    EXPECT_EQ(10u, rng.capacity());
    EXPECT_EQ(0u, rng.front());
    EXPECT_EQ(9u, rng.back());

    auto ref = 0u;
    for (const auto& v : rng)
    {
        EXPECT_EQ(ref, v);
        ref++;
    }
    EXPECT_EQ(10u, ref);
}

TEST(ring, init_same_container_to_large)
{
    auto cont = std::deque<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto rng = stdex::ring<int, 5>(cont);

    EXPECT_EQ(5u, rng.size());
    EXPECT_EQ(5u, rng.capacity());
    EXPECT_EQ(0u, rng.front());
    EXPECT_EQ(4u, rng.back());

    auto ref = 0u;
    for (const auto& v : rng)
    {
        EXPECT_EQ(ref, v);
        ref++;
    }
    EXPECT_EQ(5u, ref);
}

TEST(ring, init_begin_end)
{
    auto cont = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto rng = stdex::ring<int, 10>(begin(cont), end(cont));

    EXPECT_EQ(10u, rng.size());
    EXPECT_EQ(10u, rng.capacity());
    EXPECT_EQ(0u, rng.front());
    EXPECT_EQ(9u, rng.back());

    auto ref = 0u;
    for (const auto& v : rng)
    {
        EXPECT_EQ(ref, v);
        ref++;
    }
    EXPECT_EQ(10u, ref);
}

TEST(ring, init_begin_end_to_large)
{
    auto cont = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto rng = stdex::ring<int, 5>(begin(cont), end(cont));

    EXPECT_EQ(5u, rng.size());
    EXPECT_EQ(5u, rng.capacity());
    EXPECT_EQ(0u, rng.front());
    EXPECT_EQ(4u, rng.back());

    auto ref = 0u;
    for (const auto& v : rng)
    {
        EXPECT_EQ(ref, v);
        ref++;
    }
    EXPECT_EQ(5u, ref);
}

TEST(ring, emplace)
{
    auto r = stdex::ring<std::tuple<int, int>, 10>();
    r.emplace_front(11, 12);
    r.emplace_back(21, 22);

    EXPECT_EQ(std::make_tuple(11, 12), r.front());
    EXPECT_EQ(std::make_tuple(21, 22), r.back());
}

TEST(ring, insert)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto i = rng.begin() + 5;
    rng.insert(i, 99);

    auto ref = std::vector<int>{0, 1, 2, 3, 4, 99, 5, 6, 7, 8};
    EXPECT_TRUE(stdex::equals(begin(rng), end(rng), begin(ref), end(ref)));
}

TEST(ring, insert_begin)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    rng.insert(rng.begin(), 99);

    auto ref = std::vector<int>{99, 0, 1, 2, 3, 4, 5, 6, 7, 8};
    EXPECT_TRUE(stdex::equals(begin(rng), end(rng), begin(ref), end(ref)));
}

TEST(ring, insert_end)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    rng.insert(rng.end(), 99);

    // this is the defined behavior, we insert the item and then cull the back
    // not sure if that is the right behavior... 
    auto ref = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_TRUE(stdex::equals(begin(rng), end(rng), begin(ref), end(ref)));
}

TEST(ring, swap1)
{
    auto a = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto b = stdex::ring<int, 10>{};
    a.swap(b);

    EXPECT_EQ(0u, a.size());

    EXPECT_EQ(10u, b.size());
    EXPECT_EQ(0u, b.front());
    EXPECT_EQ(9u, b.back());
}

TEST(ring, swap2)
{
    auto a = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto b = stdex::ring<int, 10>{};
    swap(a, b);

    EXPECT_EQ(0u, a.size());

    EXPECT_EQ(10u, b.size());
    EXPECT_EQ(0u, b.front());
    EXPECT_EQ(9u, b.back());
}

TEST(ring, iterator1)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto i = 0u;
    auto iter = rng.begin();
    while (iter != rng.end())
    {
        EXPECT_EQ(i, *iter);
        iter++;
        i++;
    }
}

TEST(ring, iterator2)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto i = 0u;
    auto iter = begin(rng);
    while (iter != end(rng))
    {
        EXPECT_EQ(i, *iter);
        iter++;
        i++;
    }
}

TEST(ring, iterator1_const)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const auto& crng = rng;
    auto i = 0u;
    auto iter = crng.begin();
    while (iter != crng.end())
    {
        EXPECT_EQ(i, *iter);
        iter++;
        i++;
    }
}

TEST(ring, iterator2_const)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const auto& crng = rng;
    auto i = 0u;
    auto iter = begin(crng);
    while (iter != end(crng))
    {
        EXPECT_EQ(i, *iter);
        iter++;
        i++;
    }
}

TEST(ring, citerator1)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto i = 0u;
    auto iter = rng.cbegin();
    while (iter != rng.cend())
    {
        EXPECT_EQ(i, *iter);
        iter++;
        i++;
    }
}

TEST(ring, citerator2)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto i = 0u;
    auto iter = cbegin(rng);
    while (iter != cend(rng))
    {
        EXPECT_EQ(i, *iter);
        iter++;
        i++;
    }
}

TEST(ring, riterator1)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto i = 9u;
    auto iter = rng.rbegin();
    while (iter != rng.rend())
    {
        EXPECT_EQ(i, *iter);
        iter++;
        i--;
    }
}

TEST(ring, riterator2)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto i = 9u;
    auto iter = rbegin(rng);
    while (iter != rend(rng))
    {
        EXPECT_EQ(i, *iter);
        iter++;
        i--;
    }
}

TEST(ring, riterator1_const)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const auto& crng = rng;
    auto i = 9u;
    auto iter = crng.rbegin();
    while (iter != crng.rend())
    {
        EXPECT_EQ(i, *iter);
        iter++;
        i--;
    }
}

TEST(ring, riterator2_const)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const auto& crng = rng;
    auto i = 9u;
    auto iter = rbegin(crng);
    while (iter != rend(crng))
    {
        EXPECT_EQ(i, *iter);
        iter++;
        i--;
    }
}

TEST(ring, criterator1)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto i = 9u;
    auto iter = rng.crbegin();
    while (iter != rng.crend())
    {
        EXPECT_EQ(i, *iter);
        iter++;
        i--;
    }
}

TEST(ring, criterator2)
{
    auto rng = stdex::ring<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto i = 9u;
    auto iter = crbegin(rng);
    while (iter != crend(rng))
    {
        EXPECT_EQ(i, *iter);
        iter++;
        i--;
    }
}