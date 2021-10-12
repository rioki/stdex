// Rioki's Standard Extentions
// Copyright 2020-2021 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.

#include <gtest/gtest.h>
#include <stdex/distance.h>

TEST(distance, default_contructor)
{
    auto distance = stdex::distance{};
    ASSERT_EQ(0.0, distance.count());
}

TEST(distance, construct_m)
{
    auto distance = stdex::distance{1.2f};
    ASSERT_FLOAT_EQ(1.2f, distance.count());
}

TEST(distance, construct_km)
{
    auto distance = stdex::distance<float, std::kilo>(1.2);
    ASSERT_FLOAT_EQ(1.2f, distance.count());
}

TEST(distance, cast_km_to_m)
{
    auto distance_km = stdex::kilometer(1.2);
    auto distance_m = stdex::distance_cast<stdex::meter>(distance_km);
    ASSERT_DOUBLE_EQ(1200.0, distance_m.count());
}

TEST(distance, cast_mm_to_m)
{
    auto distance_mm = stdex::millimeter(1.2f);
    auto distance_m = stdex::distance_cast<stdex::meter>(distance_mm);
    EXPECT_NEAR(0.0012f, distance_m.count(), 0.01);
}


TEST(distance, cast_km_to_mm)
{
    auto distance_km = stdex::kilometer(1.2f);
    auto distance_mm = stdex::distance_cast<stdex::millimeter>(distance_km);
    EXPECT_NEAR(1200000.0, distance_mm.count(), 0.1);
}

TEST(distance, compare_mg_and_kg)
{
    using namespace stdex::distance_literals;

    ASSERT_TRUE(1200000_mm == 1.2_km);
}

TEST(distance, addition)
{
    using namespace stdex::distance_literals;

    ASSERT_TRUE(1.2_m == 0.6_m + 0.6_m);
}

TEST(distance, subtraction)
{
    using namespace stdex::distance_literals;

    ASSERT_TRUE(0.1_m == 0.6_m - 0.5_m);
}