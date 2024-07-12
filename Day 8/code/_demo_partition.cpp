//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 _demo_partition.cpp -o _demo_partition.exe
//g++ -std=c++17 -O3 _demo_partition.cpp -o _demo_partition.exe
//cl /Fo.\obj\ /EHsc /O2 _demo_partition.cpp /link /out:_demo_partition.exe

#include "helpers_and_types.hpp"

#include <algorithm>
#include <vector>
#include <iostream>

int main()
{
    seed_rand(now_since_epoch());

    auto xs = generate_random_ints(32, 10, 99);
    std::cout << " input: ";
    for (int x : xs) 
        std::cout << x << ' ';
    std::cout << '\n';
    auto i = rand_int(0, xs.size() - 1);
    std::swap(xs[i], xs[0]);
    std::cout << " pivot: " << xs[0] << '\n';
    auto bound = std::partition(xs.begin() + 1, xs.end(), [pivot = *xs.begin()](int x) { return x <= pivot; });
    std::swap(*(bound - 1), xs[0]);
    std::cout << "output: ";
    for (int x : xs) 
        std::cout << x << ' ';
    std::cout << '\n';

    std::cout << '\n';

    xs = generate_random_ints(32, 10, 99);
    std::cout << " input: ";
    for (int x : xs) 
        std::cout << x << ' ';
    std::cout << '\n';
    auto is_even = [](int x) { return !(x & 0x1); };
    bound = std::partition(xs.begin(), xs.end(), is_even);
    std::cout << " evens: ";
    for (auto it = xs.begin(); it != bound; ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
    std::cout << "  odds: ";
    for (auto it = bound; it != xs.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
}