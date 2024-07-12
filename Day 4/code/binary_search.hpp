//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef BINARY_SEARCH_HPP
#define BINARY_SEARCH_HPP

#include "dynamic_array.hpp"
#include <vector>
#include <cstddef>
#include <tuple>
#include <algorithm>

namespace binary_search
{
    const std::size_t NOT_FOUND = -1;

    namespace internal
    {
        template <typename Container, typename Comparer>
        std::size_t binary_search(const Container& xs, const typename Container::value_type& x, Comparer compare)
        {
            std::size_t l = 0, r = xs.size(), mid;
            while (l < r)
            {
                //mid = (r + l) / 2; //overflow case
                mid = l + (r - l) / 2; //no overflow case

                //x == xs[mid] -> 0
                //x <  xs[mid] -> < 0 (usually -1)
                //x >  xs[mid] -> > 0 (usually +1)
                int comp = compare(x, xs[mid]);
                if (comp == 0)
                    return mid;
                else if (comp < 0)
                    r = mid;
                else /* if (comp > 0) */
                    l = mid + 1;
            }
            return NOT_FOUND;
        }

        template <typename Container, typename Comparer>
        std::size_t binary_search_leftmost(const Container& xs, const typename Container::value_type& x, Comparer compare)
        {
            std::size_t l = 0, r = xs.size(), mid;
            bool found = false;
            while (l < r)
            {
                //mid = (r + l) / 2; //overflow case
                mid = l + (r - l) / 2; //no overflow case
                
                //x == xs[mid] -> 0
                //x <  xs[mid] -> < 0 (usually -1)
                //x >  xs[mid] -> > 0 (usually +1)  
                int comp = compare(x, xs[mid]);				
                if (comp > 0)
                {
                    l = mid + 1;
                }
                else /* if (comp < 0) || (comp == 0) */
                {
                    r = mid;
                    found = found || (comp == 0);
                }
            }
            return found ? l : NOT_FOUND;
        }

        template <typename Container, typename Comparer>
        std::size_t binary_search_rightmost(const Container& xs, const typename Container::value_type& x, Comparer compare)
        {
            std::size_t l = 0, r = xs.size(), mid;
            bool found = false;
            while (l < r)
            {
                //mid = (r + l) / 2; //overflow case
                mid = l + (r - l) / 2; //no overflow case

                //x == xs[mid] -> 0
                //x <  xs[mid] -> < 0 (usually -1)
                //x >  xs[mid] -> > 0 (usually +1) 
                int comp = compare(x, xs[mid]);
                if (comp >= 0)
                {
                    l = mid + 1;
                    found = found || (comp == 0);
                }
                else /* if (comp < 0) */
                {
                    r = mid;					
                }
            }
            return found ? (l - 1) : NOT_FOUND;
        }

        template <typename Container>
        std::tuple<typename Container::const_iterator, typename Container::const_iterator>
            between(const Container& xs, const typename Container::value_type& lhs, const typename Container::value_type& rhs)
        {
            //assert(lhs <= rhs);
            //assert(std::is_sorted(xs.cbegin(), xs.cend()));
            auto first = std::lower_bound(xs.cbegin(), xs.cend(), lhs);
            auto last = std::upper_bound(xs.cbegin(), xs.cend(), rhs);
            return std::make_tuple(first, last);
        }

        template <typename Container>
        std::tuple<typename Container::const_iterator, typename Container::const_iterator>
            equal_range(const Container& xs, const typename Container::value_type& x)
        {
            return std::equal_range(xs.cbegin(), xs.cend(), x);
        }
    }

    template <typename T, typename Comparer>
    std::size_t binary_search(const dynamic_array::dynamic_array<T>& xs, const T& x, Comparer compare)
    {
        return internal::binary_search(xs, x, compare);
    }

    template <typename T, typename Comparer>
    std::size_t binary_search(const std::vector<T>& xs, const T& x, Comparer compare)
    {
        return internal::binary_search(xs, x, compare);
    }

    template <typename T, typename Comparer>
    std::size_t binary_search_leftmost(const dynamic_array::dynamic_array<T>& xs, const T& x, Comparer compare)
    {
        return internal::binary_search_leftmost(xs, x, compare);
    }

    template <typename T, typename Comparer>
    std::size_t binary_search_leftmost(const std::vector<T>& xs, const T& x, Comparer compare)
    {
        return internal::binary_search_leftmost(xs, x, compare);
    }

    template <typename T, typename Comparer>
    std::size_t binary_search_rightmost(const dynamic_array::dynamic_array<T>& xs, const T& x, Comparer compare)
    {
        return internal::binary_search_rightmost(xs, x, compare);
    }

    template <typename T, typename Comparer>
    std::size_t binary_search_rightmost(const std::vector<T>& xs, const T& x, Comparer compare)
    {
        return internal::binary_search_rightmost(xs, x, compare);
    }

    template <typename T>
    std::tuple<typename dynamic_array::dynamic_array<T>::const_iterator, typename dynamic_array::dynamic_array<T>::const_iterator>
        between(const dynamic_array::dynamic_array<T>& xs, const T& lhs, const T& rhs)
    {
        return internal::between(xs, lhs, rhs);
    }

    template <typename T>
    std::tuple<typename std::vector<T>::const_iterator, typename std::vector<T>::const_iterator>
    between(const std::vector<T>& xs, const T& lhs, const T& rhs)
    {
        return internal::between(xs, lhs, rhs);
    }

    template <typename T>
    std::tuple<typename dynamic_array::dynamic_array<T>::const_iterator, typename dynamic_array::dynamic_array<T>::const_iterator>
        equal_range(const dynamic_array::dynamic_array<T>& xs, const T& x)
    {
        return internal::equal_range(xs, x);
    }

    template <typename T>
    std::tuple<typename std::vector<T>::const_iterator, typename std::vector<T>::const_iterator>
    equal_range(const std::vector<T>& xs, const T& x)
    {
        return internal::equal_range(xs, x);
    }
}

#endif /* BINARY_SEARCH_HPP */