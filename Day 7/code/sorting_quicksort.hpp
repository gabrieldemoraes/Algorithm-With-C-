//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef SORTING_QUICKSORT_HPP
#define SORTING_QUICKSORT_HPP

#include "dynamic_array.hpp"
#include <vector>
#include <cassert>
#include <cstddef>
#include <algorithm>
#include <utility>
#include <iterator>
#include <random>
#include <chrono>

namespace sorting_quicksort
{
    namespace internal
    {
        template <typename Container>
        static inline void shuffle(Container& xs)
        {
            static unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
            static std::default_random_engine rnd(seed);
            shuffle(xs.begin(), xs.end(), rnd);
        }

        template <typename Container>
        static inline std::size_t median_of_3(Container& xs, std::size_t pos0, std::size_t pos1, std::size_t pos2)
        {
            auto first = xs.begin();
            using T = typename Container::value_type;
            T& x0 = *(first + pos0); T& x1 = *(first + pos1); T& x2 = *(first + pos2);
            if (x1 < x0)
                return x2 < x0 ? (x1 < x2 ? pos2 : pos1) : pos0;
            return x2 < x1 ? (x0 < x2 ? pos2 : pos0) : pos1;
        }
        
        template <typename Container>
        static inline void quicksort(Container& xs, std::size_t first, std::size_t last)
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
            
            //swap first with median of 3
            std::size_t pos0 = first, pos1 = first + N / 2, pos2 = first + N - 1;
            std::swap(xs[median_of_3(xs, pos0, pos1, pos2)], xs[first]);
            
            auto pivot = xs.begin() + first;
            auto end = xs.begin() + last;
            auto bound = std::partition(pivot + 1, end, [&](typename Container::const_reference x) {
                return x < *pivot;
            });
            if (pivot != bound)
            {
                std::swap(*pivot, *(bound - 1));
                std::size_t p = first + std::distance(pivot, bound);
                quicksort(xs, first, p - 1);
                quicksort(xs, p, last);
            }
        }
    }

    template <typename T>
    static inline void quicksort(std::vector<T>& xs)
    {
        internal::quicksort(xs, 0, xs.size());		
    }

    template <typename T>
    static inline void quicksort(dynamic_array::dynamic_array<T>& xs)
    {
        internal::quicksort(xs, 0, xs.size());
    }

    template <typename T>
    static inline void quicksort_shuffled(std::vector<T>& xs)
    {
        internal::shuffle(xs);
        internal::quicksort(xs, 0, xs.size());
    }

    template <typename T>
    static inline void quicksort_shuffled(dynamic_array::dynamic_array<T>& xs)
    {
        internal::shuffle(xs);
        internal::quicksort(xs, 0, xs.size());
    }
}

#endif /* SORTING_QUICKSORT_HPP */