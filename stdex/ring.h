// Rioki's Standard Extentions
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
#include <deque>

#include "iterator.h"

namespace stdex
{
    template <typename T, std::size_t MS, typename Container = std::deque<T>>
    class ring
    {
    public:
        using container_type         = Container;
        using value_type             = typename Container::value_type;
        using size_type              = typename Container::size_type;
        using difference_type        = typename Container::difference_type;
        using reference              = typename Container::reference;
        using const_reference        = typename Container::const_reference;
        using pointer                = typename Container::pointer;
        using const_pointer          = typename Container::const_pointer;
        using iterator               = typename Container::iterator;
        using const_iterator         = typename Container::const_iterator;
        using reverse_iterator       = typename Container::reverse_iterator;
        using const_reverse_iterator = typename Container::const_reverse_iterator;

        ring() noexcept = default;

        explicit ring(const Container& cont)
        : container(cont) 
        {
            prune_back();
        }

        explicit ring(Container&& cont)
        : container(cont) 
        {
            prune_back();
        }

        explicit ring(std::initializer_list<T> inilst)
        : container(inilst) 
        {
            prune_back();
        }

        template <typename InputIt>
        ring(InputIt first, InputIt last)
        : container(first, last) 
        {
            prune_back();
        }

        template <typename Alloc>
        explicit ring(const Alloc& alloc)
        : container(alloc) {}

        template <typename Alloc>
        ring(const Container& cont, const Alloc& alloc)
        : container(cont, alloc) 
        {
            prune_back();
        }

        template <typename Alloc>
        ring(const Container&& cont, const Alloc& alloc)
        : container(cont, alloc)
        {
            prune_back();
        }

        template <typename InputIt, typename Alloc>
        ring(InputIt first, InputIt last, const Alloc& alloc)
        : ring(first, last) 
        {
            prune_back();
        }

        ring(const ring<T, MS, Container>& other) noexcept = default;
        ring(ring<T, MS, Container>&& other) noexcept = default;

        template <typename Alloc >
        ring(const ring<T, MS, Container>& other, const Alloc& alloc)
        : container(other.container, alloc) {}

        template <typename Alloc>
        ring(ring<T, MS, Container>&& other, const Alloc& alloc)
        : container(std::move(other.container), alloc) {}

        ~ring() = default;

        ring<T, MS, Container>& operator = (const ring<T, MS, Container>& other) noexcept = default;
        ring<T, MS, Container>& operator = (ring<T, MS, Container>&& other) noexcept = default;

        const_reference front() const noexcept
        {
            return container.front();
        }

        reference back() noexcept
        {
            return container.back();
        }

        const_reference back() const noexcept
        {
            return container.back();
        }

        const_pointer data() const noexcept
        {
            return container.data();
        }

        iterator begin() noexcept
        {
            return container.begin();
        }

        const_iterator begin() const noexcept
        {
            return container.begin();
        }

        const_iterator cbegin() const noexcept
        {
            return container.cbegin();
        }

        iterator end() noexcept
        {
            return container.end();
        }

        const_iterator end() const noexcept
        {
            return container.end();
        }

        const_iterator cend() const noexcept
        {
            return container.cend();
        }

        reverse_iterator rbegin() noexcept
        {
            return container.rbegin();
        }

        const_reverse_iterator rbegin() const noexcept
        {
            return container.rbegin();
        }

        const_reverse_iterator crbegin() const noexcept
        {
            return container.crbegin();
        }

        reverse_iterator rend() noexcept
        {
            return container.rend();
        }

        const_reverse_iterator rend() const noexcept
        {
            return container.rend();
        }

        const_reverse_iterator crend() const noexcept
        {
            return container.crend();
        }

        bool empty() const noexcept
        {
            return container.empty();
        }

        size_type size() const noexcept
        {
            return container.size();
        }

        constexpr size_type capacity() const noexcept
        {
            return MS;
        }

        void push_front(const T& value) noexcept
        {
            container.push_front(value);
            prune_back();
        }

        void push_front(T&& value) noexcept
        {
            container.push_front(value);
            prune_back();
        }

        void push_back(const T& value) noexcept
        {
            container.push_back(value);
            prune_front();
        }

        void push_back(T&& value) noexcept
        {
            container.push_back(value);
            prune_front();
        }

        template <typename... Args>
        void emplace_front(Args&&... args)
        {
            container.emplace_front(args...);
            prune_back();
        }

        template <typename... Args>
        void emplace_back(Args&&... args)
        {
            container.emplace_back(args...);
            prune_front();
        }

        void pop_front() noexcept
        {
            container.pop_front();
        }

        void pop_back() noexcept
        {
            container.pop_back();
        }

        iterator insert(iterator pos, const T& value)
        {
            auto i = container.insert(pos, value);
            prune_back();
            return i;
        }

        iterator insert(const_iterator pos, const T& value)
        {
            auto i = container.insert(pos, value);
            prune_back();
            return i;
        }

        template< class InputIt >
        iterator insert(const_iterator pos, InputIt first, InputIt last )
        {
            auto i = container.insert(pos, first, last);
            prune_back();
            return i;
        }

        template <typename... Args>
        iterator emplace(const_iterator pos, Args&&... args)
        {
            auto i = container.emplace(pos, std::forward<Args...>(args...));
            prune_back();
            return i;
        }

        void clear() noexcept
        {
            container.clear();
        }

        void swap(ring<T, MS, Container>& other) noexcept
        {
            std::swap(container, other.container);
        }

    private:
        container_type container;

        void prune_front() noexcept
        {
            if (container.size() > capacity())
            {
                auto diff = container.size() - capacity();
                auto erase_begin = std::begin(container);
                auto erase_end   = inline_advance(erase_begin, diff);
                container.erase(erase_begin, erase_end);
            }
        }

        void prune_back() noexcept
        {
            if (container.size() > capacity())
            {
                auto erase_begin = inline_advance(std::begin(container), capacity());
                auto erase_end   = std::end(container);
                container.erase(erase_begin, erase_end);
            }
        }
    };

    template <typename T, std::size_t MS, typename Container>
    void swap(ring<T, MS, Container>& a, ring<T, MS, Container>& b) noexcept
    {
        a.swap(b);
    }
}
