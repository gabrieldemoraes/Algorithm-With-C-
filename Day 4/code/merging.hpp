//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef MERGING_HPP
#define MERGING_HPP

#include <vector>
#include <cassert>
#include <cstddef>
#include <algorithm>
#include <iterator>

namespace merging
{
    template<typename T>
    static inline std::vector<T> merge_copy(const std::vector<T>& lhs, const std::vector<T>& rhs)
    {
        assert(std::is_sorted(lhs.begin(), lhs.end()));
        assert(std::is_sorted(rhs.begin(), rhs.end()));

        const std::size_t N = lhs.size() + rhs.size();
        std::vector<T> temp;
        temp.reserve(N);
        std::size_t i = 0, j = 0;
        while (i + j < N)
        {
            if (i >= lhs.size())
            {
                std::copy(rhs.begin() + j, rhs.end(), std::back_inserter(temp));
                break;
            }
            else if (j >= rhs.size())
            {
                std::copy(lhs.begin() + i, lhs.end(), std::back_inserter(temp));
                break;
            }
            else if (rhs[j] < lhs[i])
            {
                temp.push_back(rhs[j++]);
            }
            else //if (rhs[j] >= lhs[i])
            {
                temp.push_back(lhs[i++]);
            }
        }
        return std::move(temp);
    }

    template<typename T>
    static inline void inplace_merge(std::vector<T>& xs, std::size_t first, std::size_t last)
    {
        assert(first < last);
        const std::size_t mid = first + (last - first) / 2;
        std::size_t l = first, r = mid;
        assert(std::is_sorted(xs.begin(), xs.begin() + mid));
        assert(std::is_sorted(xs.begin() + mid, xs.end()));

        if (mid > 0)
        {
            while (l < r && r < last)
            {
                if (xs[r] < xs[l])
                {
                    T* l_ptr = &xs[l];
                    T* r_ptr = &xs[r];
                    //rotate [l_ptr, r_ptr] to left distance(l_ptr, r_ptr) times  
                    std::rotate(l_ptr, r_ptr, r_ptr + 1);
                    ++r;
                }
                ++l;
            }
        }

        assert(std::is_sorted(xs.begin(), xs.end()));
    }

    template<typename T>
    static inline void inplace_merge(std::vector<T>& xs)
    {
        return inplace_merge(xs, 0, xs.size());
    }
}

#endif /* MERGING_HPP */