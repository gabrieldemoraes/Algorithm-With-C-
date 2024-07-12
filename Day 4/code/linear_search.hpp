//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef LINEAR_SEARCH_HPP
#define LINEAR_SEARCH_HPP

#include "dynamic_array.hpp"
#include <vector>
#include <cstddef>

namespace linear_search
{
    const std::size_t NOT_FOUND = -1;

    static std::size_t find_first_char(const char* xs, std::size_t n, char x)
    {
        for (std::size_t i = 0; i < n; ++i)
            if (xs[i] == x)
                return i;
        return NOT_FOUND;
    }

    static std::size_t find_first_int(const int* xs, std::size_t n, int x)
    {
        for (std::size_t i = 0; i < n; ++i)
            if (xs[i] == x)
                return i;
        return NOT_FOUND;
    }

    template <typename T>
    static std::size_t find_first(const T* xs, std::size_t n, const T& x)
    {
        for (std::size_t i = 0; i < n; ++i)
            if (xs[i] == x)
                return i;
        return NOT_FOUND;
    }

    template <typename T>
    static std::size_t linear_search(const dynamic_array::dynamic_array<T>& xs, const T& x)
    {
        for (std::size_t i = 0; i < xs.size(); ++i)
            if (xs[i] == x)
                return i;
        return NOT_FOUND;
    }

    template <typename T>
    static std::size_t linear_search(const std::vector<T>& xs, const T& x)
    {
        for (std::size_t i = 0; i < xs.size(); ++i)
            if (xs[i] == x)
                return i;
        return NOT_FOUND;
    }

    template <typename T>
    static std::size_t linear_search_with_sentinel(dynamic_array::dynamic_array<T>& xs, const T& x)
    {
        std::size_t n = xs.size() - 1;
        T last = xs[n];
        xs[n] = x;
        std::size_t i = 0;
        while (xs[i] != x)
            ++i;
        xs[n] = last;
        if (i < n || xs[n] == x)
            return i;
        return NOT_FOUND;
    }

    template <typename T>
    static std::size_t linear_search_with_sentinel(std::vector<T>& xs, const T& x)
    {
        std::size_t n = xs.size() - 1;
        T last = xs[n];
        xs[n] = x;
        std::size_t i = 0;
        while (xs[i] != x)
            ++i;
        xs[n] = last;
        if (i < n || xs[n] == x)
            return i;
        return NOT_FOUND;
    }

    template<typename InputIterator, typename T>
    static InputIterator linear_search(InputIterator first, InputIterator last, const T &x)
    {
        for (; first != last; ++first)
            if (*first == x)
                return first;
        return last;
    }

    template<typename InputIterator, typename UnaryPredicate>
    static InputIterator linear_search_if(InputIterator first, InputIterator last, UnaryPredicate predicate)
    {
        for (; first != last; ++first)
            if (predicate(*first))
                return first;
        return last;
    }

    template<typename InputIterator, typename UnaryPredicate>
    static InputIterator linear_search_if_not(InputIterator first, InputIterator last, UnaryPredicate predicate)
    {
        for (; first != last; ++first)
            if (!predicate(*first))
                return first;
        return last;
    }
}

#endif /* LINEAR_SEARCH_HPP */