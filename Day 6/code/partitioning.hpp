//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef PARTITIONING_HPP
#define PARTITIONING_HPP

#include <cassert>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iterator>

namespace partitioning
{
    template <typename T>
    std::size_t inplace_partition(std::vector<T>& xs, std::size_t first, std::size_t last, std::size_t pivot)
    {
        assert(first < last && first <= pivot && pivot < last);

        std::swap(xs[first], xs[pivot]);
        T& pivot_value = xs[first];
        std::size_t i = first; //left to right
        std::size_t	j = last;  //right to left
        while (true)
        {
            while (xs[++i] < pivot_value && i != last - 1); //to the left from pivot
            //while (pivot_value < xs[--j] && j != first); //to the right from pivot
            while (pivot_value <= xs[--j] && j != first); //to the right from pivot

            if (i >= j) break; //can't swap anymore

            std::swap(xs[i], xs[j]);
        }
        std::swap(pivot_value, xs[j]); //change 'the pivot' element to 'the right to left bounded' element
        return j; //left from j is less than xs[j], otherwise is greater or equal to xs[j]
    }

    template <typename T>
    std::size_t inplace_partition(std::vector<T>& xs, std::size_t first, std::size_t last)
    {
        return inplace_partition(xs, first, last, first);
    }

    template <typename T>
    std::size_t inplace_partition(std::vector<T>& xs, std::size_t pivot = 0)
    {
        return inplace_partition(xs, 0, xs.size(), pivot);
    }

    template <typename BidirectionalIterator>
    BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last, BidirectionalIterator pivot)
    {
        using T = typename std::iterator_traits<BidirectionalIterator>::value_type;

        std::swap(*first, *pivot);
        //auto lt = [first](const auto& x) { return x < *first; };
        auto lt = [first](const T& x) { return x < *first; };
        auto bound = std::partition(std::next(first), last, lt);
        pivot = std::prev(bound);
        std::swap(*first, *pivot);
        return pivot;
    }

    template <typename BidirectionalIterator>
    BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last, std::size_t pivot = 0)
    {
        auto p = first;
        std::advance(p, pivot);
        return partition(first, last, p);
    }
}

#endif /* PARTITIONING_HPP */