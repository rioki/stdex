// Array View
// Copyright 2020-2021 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.

#pragma once

#include <cstddef>
#include <stdexcept>
#include <iterator>
#include <utility>
#include <vector>
#include <array>
#include <string>
#include <string_view>
                                                                               
namespace stdex
{
    template <typename T>
    class array_view_const_reverse_iterator
    {
    public:
        using value_type             = T;
        using const_reference        = const value_type&;
        using const_pointer          = const value_type*;

        array_view_const_reverse_iterator() = default;

        array_view_const_reverse_iterator(const_pointer i)
        : iter(i) {}

        array_view_const_reverse_iterator(const array_view_const_reverse_iterator<T>&) = default;
        array_view_const_reverse_iterator(array_view_const_reverse_iterator<T>&&) = default;
        ~array_view_const_reverse_iterator() = default;
        array_view_const_reverse_iterator<T>& operator = (const array_view_const_reverse_iterator<T>&) = default;
        array_view_const_reverse_iterator<T>& operator = (array_view_const_reverse_iterator<T>&&) = default;

        const_pointer operator -> () 
        {
            return iter;
        }

        const_reference operator * () 
        {
            return *iter;
        }

        array_view_const_reverse_iterator<T>& operator ++ ()
        {
            iter--;
            return *this;
        }

        array_view_const_reverse_iterator<T>& operator -- ()
        {
            iter++;
            return *this;
        }

        array_view_const_reverse_iterator<T> operator ++ (int)
        {
            auto old = array_view_const_reverse_iterator<T>(iter);
            iter--;
            return old;
        }

        array_view_const_reverse_iterator<T> operator -- (int)
        {
            auto old = array_view_const_reverse_iterator<T>(iter);
            iter++;
            return old;
        }

        bool operator == (const array_view_const_reverse_iterator<T>& other)
        {
            return iter == other.iter;
        }

        bool operator != (const array_view_const_reverse_iterator<T>& other)
        {
            return iter != other.iter;
        }

    private:
        const_pointer iter = nullptr;
    };


    //! Array View
    //!
    //! The array view wraps raw arrays and std containers to provide a 
    //! uniform access to contiguous data.
    template <typename T>
    class array_view
    {
    public:
        using value_type             = T;
        using size_type              = std::size_t;
        using difference_type        = std::ptrdiff_t;
        using const_reference        = const value_type&;
        using const_pointer          = const value_type*;
        using const_iterator         = const_pointer;
        using const_reverse_iterator = array_view_const_reverse_iterator<T>;

        array_view() noexcept = default;

        array_view(const_pointer d, size_type s) noexcept
        : _data(d), _size(s) {}

        array_view(const std::vector<T>& vec) noexcept
        : _data(vec.data()), _size(vec.size()) {}

        template <size_t N>
        array_view(const std::array<T, N>& arr) noexcept
        : _data(arr.data()), _size(arr.size()) {}

        array_view(const std::basic_string<T>& str) noexcept
        : _data(str.data()), _size(str.size()) {}

        array_view(const std::basic_string_view<T>& str) noexcept
        : _data(str.data()), _size(str.size()) {}

        array_view(const array_view<T>& other) noexcept = default;
        array_view(array_view<T>&& other) noexcept = default;

        ~array_view() = default;

        array_view<T>& operator = (const array_view<T>& other) noexcept = default;
        array_view<T>& operator = (array_view<T>&& other) noexcept = default;

        const_reference operator [] (size_type i) const noexcept
        {
            assert(i < _size);
            return _data[i];
        }

        const_reference at(size_type i) const
        {
            if (i < _size)
            {
                return _data[i];
            }
            else
            {
                throw std::out_of_range("array_view");
            }
        }

        const_reference front() const noexcept
        {
            assert(_size > 0);
            return _data[0];
        }

        const_reference back() const noexcept
        {
            assert(_size > 0);
            return _data[_size - 1];
        }

        const_pointer data() const noexcept
        {
            return _data;
        }

        const_iterator begin() const noexcept
        {
            return _data;
        }

        const_iterator cbegin() const noexcept
        {
            return _data;
        }

        const_iterator end() const noexcept
        {
            return _data + _size;
        }

        const_iterator cend() const noexcept
        {
            return _data + _size;
        }

        const_reverse_iterator rbegin() const noexcept
        {
            return const_reverse_iterator(end() - 1);
        }

        const_reverse_iterator crbegin() const noexcept
        {
            return const_reverse_iterator(end() - 1);
        }

        const_reverse_iterator rend() const noexcept
        {
            return const_reverse_iterator(begin() - 1);
        }

        const_reverse_iterator crend() const noexcept
        {
            return const_reverse_iterator(begin() - 1);
        }

        bool empty() const noexcept
        {
            return _size == 0;
        }

        size_type size() const noexcept
        {
            return _size;
        }

        void swap(array_view<T>& other) noexcept
        {
            std::swap(_data, other._data);
            std::swap(_size, other._size);
        }

    private:
        const_pointer _data = nullptr;
        size_type     _size = 0;
    };

    template <typename T>
    auto begin(const array_view<T>& av) noexcept
    {
        return av.begin();
    }

    template <typename T>
    auto cbegin(const array_view<T>& av) noexcept
    {
        return av.cbegin();
    }

    template <typename T>
    auto end(const array_view<T>& av) noexcept
    {
        return av.end();
    }

    template <typename T>
    auto cend(const array_view<T>& av) noexcept
    {
        return av.cend();
    }

    template <typename T>
    auto rbegin(const array_view<T>& av) noexcept
    {
        return av.rbegin();
    }

    template <typename T>
    auto crbegin(const array_view<T>& av) noexcept
    {
        return av.crbegin();
    }

    template <typename T>
    auto rend(const array_view<T>& av) noexcept
    {
        return av.rend();
    }

    template <typename T>
    auto crend(const array_view<T>& av) noexcept
    {
        return av.crend();
    }

    template <typename T>
    void swap(array_view<T>& a, array_view<T>& b) noexcept
    {
        a.swap(b);
    }

    template <typename T>
    array_view<T> make_array_view(const T* d, size_t l) noexcept
    {
        return array_view<T>(d, l);
    }
}
