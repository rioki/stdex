// Rioki's Standard Extentions
// Copyright 2020-2021 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.

#include <gtest/gtest.h>
#include <stdex/array_view.h>

TEST(array_view, default_contructor) 
{
    auto av = stdex::array_view<int>();
    EXPECT_TRUE(av.empty());
    EXPECT_EQ(0u, av.size());
}

TEST(array_view, c_array)
{
    constexpr auto array_size = 10u;
    int values[array_size] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values, array_size);
    EXPECT_FALSE(av.empty());
    for (auto i = 0u; i < av.size(); i++)
    {
        EXPECT_EQ(values[i], av[i]);
    }
}

TEST(array_view, c_array_null)
{
    auto av = stdex::array_view<int>(nullptr, 0);
    EXPECT_TRUE(av.empty());
    EXPECT_EQ(0u, av.size());
}

TEST(array_view, vector)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    EXPECT_FALSE(av.empty());
    for (auto i = 0u; i < av.size(); i++)
    {
        EXPECT_EQ(values[i], av[i]);
    }
}

TEST(array_view, vector_empty)
{
    auto values = std::vector<int>();
    auto av = stdex::array_view<int>(values);
    EXPECT_TRUE(av.empty());
    EXPECT_EQ(0u, av.size());
}

TEST(array_view, array)
{
    auto values = std::array<int, 10>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    EXPECT_FALSE(av.empty());
    for (auto i = 0u; i < av.size(); i++)
    {
        EXPECT_EQ(values[i], av[i]);
    }
}

TEST(array_view, array_empty)
{
    // is this even a real use case?
    auto values = std::array<int, 0>();
    auto av = stdex::array_view<int>(values);
    EXPECT_TRUE(av.empty());
    EXPECT_EQ(0u, av.size());
}

TEST(array_view, string)
{
    auto values = std::string{"Hello"};
    auto av = stdex::array_view<char>(values);
    EXPECT_FALSE(av.empty());
    for (auto i = 0u; i < av.size(); i++)
    {
        EXPECT_EQ(values[i], av[i]);
    }
}

TEST(array_view, string_empty)
{
    auto values = std::string{};
    auto av = stdex::array_view<char>(values);
    EXPECT_TRUE(av.empty());
    EXPECT_EQ(0u, av.size());
}

TEST(array_view, wstring)
{
    auto values = std::wstring{L"Hello"};
    auto av = stdex::array_view<wchar_t>(values);
    EXPECT_FALSE(av.empty());
    for (auto i = 0u; i < av.size(); i++)
    {
        EXPECT_EQ(values[i], av[i]);
    }
}

TEST(array_view, wstring_empty)
{
    auto values = std::wstring{};
    auto av = stdex::array_view<wchar_t>(values);
    EXPECT_TRUE(av.empty());
    EXPECT_EQ(0u, av.size());
}

TEST(array_view, string_view)
{
    auto values = std::string_view{"Hello"};
    auto av = stdex::array_view<char>(values);
    EXPECT_FALSE(av.empty());
    for (auto i = 0u; i < av.size(); i++)
    {
        EXPECT_EQ(values[i], av[i]);
    }
}

TEST(array_view, string_view_empty)
{
    auto values = std::string_view{};
    auto av = stdex::array_view<char>(values);
    EXPECT_TRUE(av.empty());
    EXPECT_EQ(0u, av.size());
}

TEST(array_view, wstring_view)
{
    auto values = std::wstring_view{L"Hello"};
    auto av = stdex::array_view<wchar_t>(values);
    EXPECT_FALSE(av.empty());
    for (auto i = 0u; i < av.size(); i++)
    {
        EXPECT_EQ(values[i], av[i]);
    }
}

TEST(array_view, wstring_view_empty)
{
    auto values = std::wstring_view{};
    auto av = stdex::array_view<wchar_t>(values);
    EXPECT_TRUE(av.empty());
    EXPECT_EQ(0u, av.size());
}

TEST(array_view, c_string)
{
    auto values = "Hello";
    auto av = stdex::array_view<char>(values, std::strlen(values));
    EXPECT_FALSE(av.empty());
    for (auto i = 0u; i < av.size(); i++)
    {
        EXPECT_EQ(values[i], av[i]);
    }
}

TEST(array_view, c_string_empty)
{
    auto values = "";
    auto av = stdex::array_view<char>(values, std::strlen(values));
    EXPECT_TRUE(av.empty());
    EXPECT_EQ(0u, av.size());
}

TEST(array_view, at_throws)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    EXPECT_THROW(av.at(10u), std::out_of_range);
}

TEST(array_view, font_and_back)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    EXPECT_EQ(0, av.front());
    EXPECT_EQ(9, av.back());
}

TEST(array_view, data)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    EXPECT_EQ(values.data(), av.data());
}

TEST(array_view, swap1)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    auto bv = stdex::array_view<int>();
    av.swap(bv);
    EXPECT_TRUE(av.empty());
    EXPECT_EQ(0u, av.size());
    EXPECT_FALSE(bv.empty());
    for (auto i = 0u; i < bv.size(); i++)
    {
        EXPECT_EQ(values[i], bv[i]);
    }
}

TEST(array_view, swap2)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    auto bv = stdex::array_view<int>();
    swap(av, bv);
    EXPECT_TRUE(av.empty());
    EXPECT_EQ(0u, av.size());
    EXPECT_FALSE(bv.empty());
    for (auto i = 0u; i < bv.size(); i++)
    {
        EXPECT_EQ(values[i], bv[i]);
    }
}

TEST(array_view, iterator1)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    auto i = 0u;
    auto iter = av.begin();
    while (iter != av.end())
    {
        EXPECT_EQ(values[i], *iter);
        iter++;
        i++;
    }
}

TEST(array_view, iterator2)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    auto i = 0u;
    auto iter = begin(av);
    while (iter != end(av))
    {
        EXPECT_EQ(values[i], *iter);
        iter++;
        i++;
    }
}

TEST(array_view, citerator1)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    auto i = 0u;
    auto iter = av.cbegin();
    while (iter != av.cend())
    {
        EXPECT_EQ(values[i], *iter);
        iter++;
        i++;
    }
}

TEST(array_view, citerator2)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    auto i = 0u;
    auto iter = cbegin(av);
    while (iter != cend(av))
    {
        EXPECT_EQ(values[i], *iter);
        iter++;
        i++;
    }
}

TEST(array_view, riterator1)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    auto i = 9u;
    auto iter = av.rbegin();
    while (iter != av.rend())
    {
        EXPECT_EQ(values[i], *iter);
        iter++;
        i--;
    }
}

TEST(array_view, riterator2)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    auto i = 9u;
    auto iter = rbegin(av);
    while (iter != rend(av))
    {
        EXPECT_EQ(values[i], *iter);
        iter++;
        i--;
    }
}

TEST(array_view, criterator1)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    auto i = 9u;
    auto iter = av.crbegin();
    while (iter != av.crend())
    {
        EXPECT_EQ(values[i], *iter);
        iter++;
        i--;
    }
}

TEST(array_view, criterator2)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    auto i = 9u;
    auto iter = crbegin(av);
    while (iter != crend(av))
    {
        EXPECT_EQ(values[i], *iter);
        iter++;
        i--;
    }
}

TEST(array_view, for_each)
{
    auto values = std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto av = stdex::array_view<int>(values);
    auto i = 0u;
    for (const auto& v : values)
    {
        EXPECT_EQ(values[i], v);
        i++;
    }
}
