// Rioki's Standard Extentions
// Copyright 2020-2021 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.

#include <gtest/gtest.h>
#include <stdex/mass.h>

TEST(mass, default_contructor)
{
    auto mass = stdex::mass{};
    ASSERT_EQ(0.0, mass.count());
}

TEST(mass, construct_g)
{
    auto mass = stdex::mass{1.2f};
    ASSERT_FLOAT_EQ(1.2f, mass.count());
}

TEST(mass, construct_kg)
{
    auto mass = stdex::mass<float, std::kilo>(1.2);
    ASSERT_FLOAT_EQ(1.2f, mass.count());
}

TEST(mass, cast_kg_to_g)
{
    auto mass_kg = stdex::kilogram(1.2);
    auto mass_g = stdex::mass_cast<stdex::gram>(mass_kg);
    ASSERT_DOUBLE_EQ(1200.0, mass_g.count());
}

TEST(mass, cast_mg_to_g)
{
    auto mass_mg = stdex::milligram(1.2f);
    auto mass_g = stdex::mass_cast<stdex::gram>(mass_mg);
    EXPECT_NEAR(0.0012f, mass_g.count(), 0.01);
}


TEST(mass, cast_kg_to_mg)
{
    auto mass_kg = stdex::kilogram(1.2f);
    auto mass_mg = stdex::mass_cast<stdex::milligram>(mass_kg);
    EXPECT_NEAR(1200000.0, mass_mg.count(), 0.1);
}

TEST(mass, compare_mg_and_kg)
{
    using namespace stdex::mass_literals;

    ASSERT_TRUE(1200000_mg == 1.2_kg);
}