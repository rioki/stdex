 // Rioki's Standard Extentions
// Copyright 2020-2021 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.

#pragma once

#include <iterator>

namespace stdex
{
    //! Test two iterator ranges for equality.
    //!
    //! Two iterator ranges are equal when they are the samen length and each
    //! element in the range is equal. 
    //!
    //! @param begin1 the beginning of range one
    //! @param end1 the ending of range one
    //! @param begin2 the beginning of range two
    //! @param end2 the ending of range two
    template <typename Iter1, typename Iter2>
    bool equals(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2) noexcept
    {
        auto i1 = begin1;
        auto i2 = begin2;
        while (i1 != end1 && i2 != end2)
        {
            if (!(*i1 == *i2))
            {
                return false;
            }
            ++i1;
            ++i2;
        }
        return i1 == end1 && i2 == end2;
    }
}
