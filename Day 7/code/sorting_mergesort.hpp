//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef SORTING_MERGESORT_HPP
#define SORTING_MERGESORT_HPP

#include "dynamic_array.hpp"
#include <vector>
#include <cassert>
#include <cstddef>
#include <utility>
#include <algorithm>

namespace sorting_mergesort
{
    namespace internal
    {
        template <typename Container>
        static inline void mergesort(Container& xs, std::size_t first, std::size_t last)
        {
            assert(first <= last);
            
            const std::size_t N = last - first;
            if (N < 2)
            {
                return;
            }
            if (N == 2)
            {
                if (xs[first + 1] < xs[first])
                    std::swap(xs[first + 1], xs[first]);
                return;
            }

            const std::size_t mid = N / 2;
            mergesort(xs, first, first + mid);
            mergesort(xs, first + mid, last);

            using ptr_type = typename Container::pointer;
            ptr_type beg_ptr = &xs[first];
            ptr_type mid_ptr = beg_ptr + mid;
            ptr_type end_ptr = beg_ptr + N;
            std::inplace_merge(beg_ptr, mid_ptr, end_ptr);
        }
    }

    template <typename T>
    static inline void mergesort(std::vector<T>& xs, std::size_t first, std::size_t last)
    {
        internal::mergesort(xs, first, last);
    }

    template <typename T>
    static inline void mergesort(std::vector<T>& xs)
    {
        internal::mergesort(xs, 0, xs.size());
    }

    template <typename T>
    static inline void mergesort(dynamic_array::dynamic_array<T>& xs, std::size_t first, std::size_t last)
    {
        internal::mergesort(xs, first, last);
    }

    template <typename T>
    static inline void mergesort(dynamic_array::dynamic_array<T>& xs)
    {
        internal::mergesort(xs, 0, xs.size());
    }
}

#endif /* SORTING_MERGESORT_HPP */
