//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 is_sorted.cpp -o is_sorted.exe
//cl /Fo.\obj\ /EHsc /O2 is_sorted.cpp /link /out:is_sorted.exe

#include "helpers_and_types.hpp"

#include <vector>
#include <functional>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <iomanip>

namespace internal
{
    template<typename ForwardIterator, typename Compare>
    bool is_sorted(ForwardIterator first, ForwardIterator last, Compare compare)
    {
        if (first != last)
        {
            ForwardIterator next = first;
            while (++next != last)
            {
                if (!compare(*first, *next))
                    return false;
                first = next;
            }
        }
        return true;
    }

    template<typename ForwardIterator>
    bool is_sorted(ForwardIterator first, ForwardIterator last) 
    {
        return internal::is_sorted(first, last, std::less_equal<typename std::iterator_traits<ForwardIterator>::value_type>());
    }
}

int main()
{
    seed_rand(now_since_epoch());

    std::vector<int> xs = generate_ordered_random_ints(25, 1, 9); //ordered
    std::vector<int> ys = generate_random_ints(25, 1, 9); //highly likely unordered
    
    std::cout << "Input: ";
    std::copy(xs.begin(), xs.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    std::cout << "Is sorted ascending: " << std::boolalpha << internal::is_sorted(xs.begin(), xs.end()) << '\n';
    std::cout << "Is sorted ascending: " << std::boolalpha << std::is_sorted(xs.begin(), xs.end()) << "\n\n";
    
    std::cout << "Input: ";
    std::copy(ys.begin(), ys.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    std::cout << "Is sorted ascending: " << std::boolalpha << internal::is_sorted(ys.begin(), ys.end()) << '\n';
    std::cout << "Is sorted ascending: " << std::boolalpha << std::is_sorted(ys.begin(), ys.end()) << "\n\n";
    
    std::cout << "Input: ";
    std::copy(xs.rbegin(), xs.rend(), std::ostream_iterator<int>(std::cout, " ")); //reverse iterator (right to left)
    std::cout << "\n";
    std::cout << "Is sorted descending: " << std::boolalpha << internal::is_sorted(xs.rbegin(), xs.rend(), std::greater_equal<int>()) << '\n';
    std::cout << "Is sorted descending: " << std::boolalpha << std::is_sorted(xs.rbegin(), xs.rend(), std::greater<int>()) << "\n\n";

    std::cout << "Input: ";
    std::reverse(xs.begin(), xs.end());
    std::copy(xs.begin(), xs.end(), std::ostream_iterator<int>(std::cout, " ")); //iterator (left to right)
    std::cout << "\n";
    std::cout << "Is sorted descending: " << std::boolalpha << internal::is_sorted(xs.begin(), xs.end(), std::greater_equal<int>()) << '\n';
    std::cout << "Is sorted descending: " << std::boolalpha << std::is_sorted(xs.begin(), xs.end(), std::greater<int>()) << '\n';
}