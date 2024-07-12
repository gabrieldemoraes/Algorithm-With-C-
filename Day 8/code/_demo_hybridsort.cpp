//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 _demo_hybridsort.cpp -o _demo_hybridsort.exe
//g++ -std=c++17 -O3 _demo_hybridsort.cpp -o _demo_hybridsort.exe
//cl /Fo.\obj\ /EHsc /O2 _demo_hybridsort.cpp /link /out:_demo_hybridsort.exe
//cl /Fo.\obj\ /EHsc /std:c++17 /O2 _demo_hybridsort.cpp /link /out:_demo_hybridsort.exe

#include "helpers_and_types.hpp"

#include <cstddef>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>

template <typename T>
void insertsort(std::vector<T>& xs, std::size_t i, std::size_t j)
{
    const std::size_t N = j - i;
    for (std::size_t ii = i + 1; ii < j; ++ii)
    {
        for (std::size_t jj = ii; jj > i; --jj)
        {
            if (xs[jj] < xs[jj - 1]) std::swap(xs[jj], xs[jj - 1]);
            else break;
        }
    }
}

template <typename T>
void insertsort(std::vector<T>& xs)
{
    insertsort(xs, 0, xs.size());
}

template <typename T>
std::size_t median_of_3(std::vector<T>& xs, std::size_t pos0, std::size_t pos1, std::size_t pos2)
{
    auto it = xs.begin();
    #if __cplusplus >= 201703L //is C++ 17
    if constexpr (sizeof(T) <= 64)
    {
        //std::cout << "by copy\n";
        T x0 = *(it + pos0); T x1 = *(it + pos1); T x2 = *(it + pos2);
        if (x1 < x0)
            return x2 < x0 ? (x1 < x2 ? pos2 : pos1) : pos0;
        return x2 < x1 ? (x0 < x2 ? pos2 : pos0) : pos1;
    }
    else
    {
        goto median_of_3_by_cref;
    }
    #else //!C++ 17
    median_of_3_by_cref:
    {
        //std::cout << "by cref\n";
        const T& x0 = *(it + pos0); const T& x1 = *(it + pos1); const T& x2 = *(it + pos2);
        if (x1 < x0)
            return x2 < x0 ? (x1 < x2 ? pos2 : pos1) : pos0;
        return x2 < x1 ? (x0 < x2 ? pos2 : pos0) : pos1;
    }
    #endif
}

template <typename T>
void quicksort(std::vector<T>& xs, std::size_t i, std::size_t j, std::size_t depth)
{
    const std::size_t N = j - i;

    /*
    std::cout << "  size: " << std::setw(2) << N 
              << " depth: " << std::setw(2) << depth 
              << " i: " << std::setw(2) << i 
              << " j: " << std::setw(2) << j << '\n';
    */

    //base case
    if (N < 2)
    {
        return;
    }
    if (N == 2)
    {
        if (xs[i + 1] < xs[i])
            std::swap(xs[i + 1], xs[i]);
        return;
    }

    //change algorithm
    const std::size_t THRESHOLD = 8;
    if (N <= THRESHOLD)
    {
        insertsort(xs, i, j);
        return;
    }

    //swap first with median of 3
    std::swap(xs[median_of_3(xs, i, i + N / 2, i + N - 1)], xs[i]);
    
    auto pivot = xs.begin() + i;
    auto end = xs.begin() + j;
    auto bound = std::partition(pivot + 1, end, [pivot](const T& x) {
        return x < *pivot;
    });
    if (pivot != bound)
    {
        //recursive case
        //std::swap(*pivot, *(bound - 1));
        //or
        std::iter_swap(pivot, bound - 1);
        std::size_t p = i + std::distance(pivot, bound);
        quicksort(xs, i, p - 1, depth + 1);
        quicksort(xs, p, j, depth + 1);
    }
}

template <typename T>
void quicksort(std::vector<T>& xs)
{
    quicksort(xs, 0, xs.size(), 0);
}

int main()
{
    seed_rand(now_since_epoch());
    std::vector<int> ints = generate_random_ints(32, 1, 9);

    std::cout << " input: ";
    for(int i : ints) std::cout << i << ' ';
    std::cout << '\n';

    //insertsort(ints);
    quicksort(ints);
    
    std::cout << "output: ";
    for(int i : ints) std::cout << i << ' ';
    std::cout << '\n';

    std::cout << "sorted: " << std::boolalpha << std::is_sorted(ints.begin(), ints.end());

    return 0;
}