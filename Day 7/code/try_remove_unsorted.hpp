//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef TRY_REMOVE_UNSORTED_HPP
#define TRY_REMOVE_UNSORTED_HPP

#include <vector>
#include <cstddef>
#include <iterator>
#include <algorithm>

namespace try_remove_unsorted
{
    template<typename T>
    static inline bool try_remove_unsorted
    (
        std::vector<T>& xs, 
        std::size_t pos
    )
    {
        if (pos < xs.size())
        {
            std::swap(xs[pos], xs[xs.size() - 1]);
            xs.pop_back();
            return true;
        }
        return false;
    }

    template<typename T>
    static inline bool try_remove_unsorted
    (
        std::vector<T>& xs, 
        typename std::vector<T>::iterator it
    )
    {
        if (it != xs.end())
        {
            std::iter_swap(it, std::prev(xs.begin() + xs.size()));
            xs.pop_back();
            return true;
        }
        return false;
    }
}

#endif /* TRY_REMOVE_UNSORTED_HPP */