// Rioki's Standard Extentions
// Copyright 2020-2021 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.

#pragma once

#include <ratio>

namespace stdex
{
#ifndef _IS_RATIO_
#define _IS_RATIO_
    template <class _Ty>
    constexpr bool is_ratio_v = false;
    template <intmax_t R1, intmax_t R2>
    constexpr bool is_ratio_v<std::ratio<R1, R2>> = true;
#endif

    template <typename T = float, typename U = std::ratio<1>>
    class mass
    {
    public:
        using rep = T;
        using unit = U;

        static_assert(std::is_arithmetic_v<T>, "type must be arithmetic");
        static_assert(is_ratio_v<U>, "unit not an instance of std::ratio");

        mass() noexcept = default;

        constexpr mass(T v) noexcept
        : value(v) {}

        template <typename T2>
        constexpr mass(T2 v) noexcept
        : value(static_cast<T>(v)) {}

        mass(const mass<T, U>&) noexcept = default;
        mass(mass<T, U>&&) noexcept = default;

        ~mass() = default;

        mass<T, U>& operator = (const mass<T, U>&) noexcept = default;
        mass<T, U>& operator = (mass<T, U>&&) noexcept = default;

        constexpr T count() const
        {
            return value;
        }

        constexpr operator T () const
        {
            return value;
        }

    private:
        T value = T(0);
    };

    template <class TO, class T, class U>
    constexpr TO mass_cast(const mass<T, U>& m) noexcept
    {
        using div = std::ratio_divide<U, typename TO::unit>;
        using ComonType = std::common_type_t<typename TO::rep, T, intmax_t>;

        if (div::den == 1)
        {
            if (div::num == 1)
            {
                return TO(m.count());
            }
            else
            {
                return TO(static_cast<ComonType>(m.count()) * static_cast<ComonType>(div::num));
            }
        } else
        {
            if (div::num == 1)
            {
                return TO(static_cast<ComonType>(m.count()) / static_cast<ComonType>(div::den));
            }
            else
            {
                return TO(static_cast<ComonType>(m.count()) * static_cast<ComonType>(div::num) / static_cast<ComonType>(div::den));
            }
        }
    }

    using milligram = mass<double, std::milli>;
    using gram      = mass<double>;
    using kilogram  = mass<double, std::kilo>;
    using ton       = mass<double, std::mega>;

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator == (const mass<T1, U1>& a, const mass<T2, U2>& b) noexcept
    {
        auto b2 = mass_cast<mass<T1, U1>>(b);
        return std::abs(a.count() - b2.count()) < T1(1.e-4f);
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator != (const mass<T1, U1>& a, const mass<T2, U2>& b) noexcept
    {
        return !(a == b);
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator < (const mass<T1, U1>& a, const mass<T2, U2>& b) noexcept
    {
        auto b2 = mass_cast<mass<T1, U1>>(b);
        return a.count() < b2.count();
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator > (const mass<T1, U1>& a, const mass<T2, U2>& b) noexcept
    {
        auto b2 = mass_cast<mass<T1, U1>>(b);
        return a.count() > b2.count();
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator <= (const mass<T1, U1>& a, const mass<T2, U2>& b) noexcept
    {
        return a == b || a < b;
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator >= (const mass<T1, U1>& a, const mass<T2, U2>& b) noexcept
    {
        return a == b || a > b;
    }

    namespace mass_literals
    {
        constexpr milligram operator "" _mg(long double value)
        {
            return milligram(value);
        }

        constexpr gram operator "" _g(long double value)
        {
            return gram(value);
        }

        constexpr kilogram operator "" _kg(long double value)
        {
            return kilogram(value);
        }

        constexpr ton operator "" _t(long double value)
        {
            return ton(value);
        }

        constexpr milligram operator "" _mg(unsigned long long int value)
        {
            return milligram(value);
        }

        constexpr gram operator "" _g(unsigned long long int value)
        {
            return gram(value);
        }

        constexpr kilogram operator "" _kg(unsigned long long int value)
        {
            return kilogram(value);
        }

        constexpr ton operator "" _t(unsigned long long int value)
        {
            return ton(value);
        }
    }
}
