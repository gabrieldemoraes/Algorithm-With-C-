//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 _demo_heapsort.cpp -o _demo_heapsort.exe
//cl /Fo.\obj\ /EHsc /O2 _demo_heapsort.cpp /link /out:_demo_heapsort.exe

#include "helpers_and_types.hpp"

#include <cstddef>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iostream>

#define RandomAccessIterator typename
#define Comparer typename

template <RandomAccessIterator RandomIt, Comparer Comp>
void heapsort(RandomIt first, RandomIt last, Comp predicate)
{
    if (std::distance(first, last) > 1)
    {
        std::make_heap(first, last, predicate);
        while (first != last)
        {
            std::pop_heap(first, last, predicate);
            --last;
        }
    }
}

template <RandomAccessIterator RandomIt, Comparer Comp>
void heapsort(RandomIt first, RandomIt middle, RandomIt last, Comp predicate)
{
    if (std::distance(first, last) > 1)
    {
        std::make_heap(first, middle, predicate);
        
        for (RandomIt it = middle; it != last; ++it)
        {
            if (predicate(*it, *first))
            {
                std::swap(*it, *first);
                std::make_heap(first, middle, predicate); //sift_down
            }    
        }
        
        while (first != middle)
        {
            std::pop_heap(first, middle, predicate);
            --middle;
        }
    }
}

void test_partial_sort_aux(std::vector<int> xs, std::size_t middle)
{
    std::cout << "       input: ";
    for(int x : xs) std::cout << x << ' ';
    std::cout << "- middle: " << middle;
    std::cout << '\n';

    std::vector<int> xs_bkp = xs;
    
    std::partial_sort(xs.begin(), xs.begin() + middle, xs.end(), std::less<int>{});
    std::cout << "partial_sort: ";
    for(int x : xs) std::cout << x << ' ';
    std::cout << '\n';

    heapsort(xs_bkp.begin(), xs_bkp.begin() + middle, xs_bkp.end(), std::less<int>{});
    std::cout << "    heapsort: ";
    for(int x : xs_bkp) std::cout << x << ' ';    
    std::cout << '\n';

    std::cout << "-----------\n";
}

void test_partial_sort()
{
    test_partial_sort_aux({ 6, 5, 2, 2, 3, 9, 3, 9, 8, 6 }, 5);
    test_partial_sort_aux({ 5, 8, 3, 8, 3, 8, 6, 2, 9, 5 }, 5);
    test_partial_sort_aux({ 9, 9, 2, 7, 2, 9, 8, 3, 8, 4 }, 5);
    test_partial_sort_aux(generate_random_ints(10, 1, 9), 5);
    test_partial_sort_aux(generate_random_ints(10, 1, 9), 5);

    std::cout << "-----------\n";

    test_partial_sort_aux({ 6, 5, 2, 2, 3, 9, 3, 9, 8, 6 }, 3);
    test_partial_sort_aux({ 5, 8, 3, 8, 3, 8, 6, 2, 9, 5 }, 3);
    test_partial_sort_aux({ 9, 9, 2, 7, 2, 9, 8, 3, 8, 4 }, 3);
    test_partial_sort_aux(generate_random_ints(10, 1, 9), 3);
    test_partial_sort_aux(generate_random_ints(10, 1, 9), 3);
}

int main()
{
    seed_rand(now_since_epoch());
    std::vector<int> ints = generate_random_ints(10, 1, 9);
    
    //heapsort(ints.begin(), ints.end(), std::less<int>{});
    heapsort(ints.begin(), ints.end(), std::greater<int>{});
    
    for(int i : ints) std::cout << i << ' ';
    std::cout << '\n';
    
    ints = generate_random_ints(10, 1, 9);  
    
    std::cout << "before: ";
    for(int i : ints) std::cout << i << ' ';    
        
    auto mid = ints.size() / 2;
    std::cout << "- middle: " << mid;
    std::cout << '\n';

    //heapsort(ints.begin(), middle, ints.end(), std::less<int>{});
    std::partial_sort(ints.begin(), ints.begin() + mid, ints.end(), std::less<int>{});

    std::cout << " after: ";
    for(int i : ints) std::cout << i << ' ';
    std::cout << '\n';

    std::cout << "===========\n";

    test_partial_sort();

    return 0;
}