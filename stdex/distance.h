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
    class distance
    {
    public:
        using rep = T;
        using unit = U;

        static_assert(std::is_arithmetic_v<T>, "type must be arithmetic");
        static_assert(is_ratio_v<U>, "unit not an instance of std::ratio");

        distance() noexcept = default;

        constexpr distance(T v) noexcept
        : value(v) {}

        template <typename T2>
        constexpr distance(T2 v) noexcept
        : value(static_cast<T>(v)) {}

        distance(const distance<T, U>&) noexcept = default;
        distance(distance<T, U>&&) noexcept = default;

        ~distance() = default;

        distance<T, U>& operator = (const distance<T, U>&) noexcept = default;
        distance<T, U>& operator = (distance<T, U>&&) noexcept = default;

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
    constexpr TO distance_cast(const distance<T, U>& m) noexcept
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

    using millimeter = distance<double, std::milli>;
    using centimeter = distance<double, std::centi>;
    using decimeter  = distance<double, std::deci>;
    using meter      = distance<double>;
    using kilometer  = distance<double, std::kilo>;

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator == (const distance<T1, U1>& a, const distance<T2, U2>& b) noexcept
    {
        // not sure if that is the best, but that is what is simple to implement
        auto b2 = distance_cast<distance<T1, U1>>(b);
        return std::abs(a.count() - b2.count()) < T1(1.e-4f);
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator != (const distance<T1, U1>& a, const distance<T2, U2>& b) noexcept
    {
        return !(a == b);
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator < (const distance<T1, U1>& a, const distance<T2, U2>& b) noexcept
    {
        auto b2 = distance_cast<distance<T1, U1>>(b);
        return a.count() < b2.count();
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator > (const distance<T1, U1>& a, const distance<T2, U2>& b) noexcept
    {
        auto b2 = distance_cast<distance<T1, U1>>(b);
        return a.count() > b2.count();
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator <= (const distance<T1, U1>& a, const distance<T2, U2>& b) noexcept
    {
        return a == b || a < b;
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr bool operator >= (const distance<T1, U1>& a, const distance<T2, U2>& b) noexcept
    {
        return a == b || a > b;
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr distance<T1, U1> operator + (const distance<T1, U1>& a, const distance<T2, U2>& b) noexcept
    {
        auto b2 = distance_cast<distance<T1, U1>>(b);
        return distance<T1, U1>(a.count() + b2.count());
    }

    template <typename T1, typename U1, typename T2, typename U2>
    constexpr distance<T1, U1> operator - (const distance<T1, U1>& a, const distance<T2, U2>& b) noexcept
    {
        auto b2 = distance_cast<distance<T1, U1>>(b);
        return distance<T1, U1>(a.count() - b2.count());
    }

    template <typename T1, typename U1, typename T2>
    constexpr distance<T1, U1> operator * (const distance<T1, U1>& a, const T2 b) noexcept
    {
        return distance_cast<distance<T1, U1>>(a.count() * b);
    }

    template <typename T1, typename T2, typename U2>
    constexpr distance<T2, U2> operator * (const T1 a, const distance<T2, U2>& b) noexcept
    {
        return distance_cast<distance<T2, U2>>(a * b.count());
    }

    template <typename T1, typename U1, typename T2>
    constexpr distance<T1, U1> operator / (const distance<T1, U1>& a, const T2 b) noexcept
    {
        return distance<T1, U1>(a.count() / b);
    }

    template <typename T1, typename T2, typename U2>
    constexpr distance<T2, U2> operator / (const T1 a, const distance<T2, U2>& b) noexcept
    {
        return distance<T2, U2>(a / b.count());
    }

    namespace distance_literals
    {
        constexpr millimeter operator "" _mm(long double value)
        {
            return millimeter(value);
        }

        constexpr centimeter operator "" _cm(long double value)
        {
            return centimeter(value);
        }

        constexpr decimeter operator "" _dm(long double value)
        {
            return decimeter(value);
        }

        constexpr meter operator "" _m(long double value)
        {
            return meter(value);
        }

        constexpr kilometer operator "" _km(long double value)
        {
            return kilometer(value);
        }

        constexpr millimeter operator "" _mm(unsigned long long int value)
        {
            return millimeter(value);
        }

        constexpr centimeter operator "" _cm(unsigned long long int value)
        {
            return centimeter(value);
        }

        constexpr decimeter operator "" _dm(unsigned long long int value)
        {
            return decimeter(value);
        }

        constexpr meter operator "" _m(unsigned long long int value)
        {
            return meter(value);
        }

        constexpr kilometer operator "" _km(unsigned long long int value)
        {
            return kilometer(value);
        }
    }
}
