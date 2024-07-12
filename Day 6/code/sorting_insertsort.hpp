//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef SORTING_INSERTSORT_HPP
#define SORTING_INSERTSORT_HPP

#include "dynamic_array.hpp"
#include <vector>
#include <cstddef>
#include <utility>

namespace sorting_insertsort
{
    namespace internal
    {
        template <typename Container>
        static inline void insertsort(Container& xs)
        {
            const std::size_t N = xs.size();
            for (std::size_t i = 1; i < N; ++i)
            {
                for (std::size_t j = i; j > 0; --j)
                {
                    if (xs[j] < xs[j - 1])
                        std::swap(xs[j], xs[j - 1]);
                    else
                        break;
                }
            }
        }
    }

    template <typename T>
    static inline void insertsort(std::vector<T>& xs)
    {
        internal::insertsort(xs);
    }

    template <typename T>
    static inline void insertsort(dynamic_array::dynamic_array<T>& xs)
    {
        internal::insertsort(xs);
    }
}

#endif /* SORTING_INSERTSORT_HPP */