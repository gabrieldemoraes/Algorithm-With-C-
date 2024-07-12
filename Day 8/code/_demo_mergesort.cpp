//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 _demo_mergesort.cpp -o _demo_mergesort.exe
//cl /Fo.\obj\ /EHsc /O2 _demo_mergesort.cpp /link /out:_demo_mergesort.exe

#include "helpers_and_types.hpp"

#include <cstddef>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

template <typename Container>
void mergesort(Container& xs, std::size_t i, std::size_t j)
{
    const std::size_t N = j - i;
    
    //base case
    if (N < 2)
        return;
    if (N == 2 && xs[i + 1] < xs[i])
    {
        std::swap(xs[i + 1], xs[i]);
        return;
    }
    
    //recursive case
    const std::size_t mid = N / 2;
    mergesort(xs, i, i + mid);
    mergesort(xs, i + mid, j);

    //auto first = xs.begin(), a = first + i, b = first + i + mid, c = first + j;
    auto a = xs.begin() + i, b = a + mid, c = xs.begin() + j;
    std::inplace_merge(a, b, c); //[a, b) [b, c)
}

int main()
{
    seed_rand(now_since_epoch());
    std::vector<int> ints = generate_random_ints(10, 1, 9);

    std::cout << " input: ";
    for(int i : ints) std::cout << i << ' ';
    std::cout << '\n';

    mergesort(ints, 0, ints.size());
    
    std::cout << "output: ";
    for(int i : ints) std::cout << i << ' ';
    std::cout << '\n';

    std::cout << "sorted: " << std::boolalpha << std::is_sorted(ints.begin(), ints.end());

    return 0;
}
