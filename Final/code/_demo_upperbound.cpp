//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 _demo_upperbound.cpp -o _demo_upperbound.exe
//cl /Fo.\obj\ /EHsc /O2 _demo_upperbound.cpp /link /out:_demo_upperbound.exe

#include "helpers_and_types.hpp"

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

int main()
{
    seed_rand(now_since_epoch());
    std::vector<int> ints = generate_random_ints(100, 1, 9);
    
    std::sort(ints.begin(), ints.end());
    
    auto it = ints.begin();
    while (it != ints.end())
    {
        auto it2 = std::upper_bound(it, ints.end(), *it);
        std::cout << *it << ' ' << std::distance(it, it2) << '\n';
        it = it2;
    }

    return 0;
}