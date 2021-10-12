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
    template <typename Iter, typename Diff>
    Iter inline_advance(const Iter& i, Diff diff)
    {
        auto r = i;
        std::advance(r, diff);
        return r;
    }
}
