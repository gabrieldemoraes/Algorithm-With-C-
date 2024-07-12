//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef SORTING_HEAPSORT_HPP
#define SORTING_HEAPSORT_HPP

#include "dynamic_array.hpp"
#include <vector>
#include <cstddef>
#include <functional>
#include <algorithm>

namespace sorting_heapsort
{
    namespace internal
    {
        template <typename Container, typename Compare>
        static inline void heapsort(Container& xs, Compare comp)
        {
            if (xs.size() > 1)
            {
                using ptr_type = typename Container::pointer;
                ptr_type beg_ptr = &xs[0];
                ptr_type end_ptr = beg_ptr + xs.size();

                std::make_heap(beg_ptr, end_ptr, comp);
                while (beg_ptr != end_ptr)
                {
                    std::pop_heap(beg_ptr, end_ptr, comp);
                    --end_ptr;
                }
            }
        }
    }

    template <typename T>
    static inline void heapsort(std::vector<T>& xs)
    {
        internal::heapsort(xs, std::less<T>());
    }

    template <typename T>
    static inline void heapsort(dynamic_array::dynamic_array<T>& xs)
    {
        internal::heapsort(xs, std::less<T>());
    }
}

#endif /* SORTING_HEAPSORT_HPP */