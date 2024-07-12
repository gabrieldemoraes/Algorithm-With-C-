//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 counting_distincts.cpp -o counting_distincts.exe
//cl /Fo.\obj\ /EHsc /O2 counting_distincts.cpp /link /out:counting_distincts.cpp

#include "helpers_and_types.hpp"

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <iterator>

void counting_distincts_when_unordered()
{
    std::vector<int> xs = generate_random_ints(25, 1, 9);
    
    std::cout << "Input:\n";
    std::copy(xs.begin(), xs.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n\n";

    std::map<int, int> counter;
    for (int i : xs)
    {
        auto iter = counter.find(i);
        if (iter != counter.end())
        {
            //iter->first (key)
            //iter->second (value)
            ++iter->second;
        }
        else
        {
            counter.emplace(i, 1);
        }
    }
    std::cout << "Output:\n";
    for (auto kv : counter)
    {
        std::cout << kv.first << ' ' << kv.second << '\n';
    }
}

void counting_distincts_when_ordered()
{
    std::vector<int> xs = generate_ordered_random_ints(25, 1, 9);

    std::cout << "Input:\n";
    std::copy(xs.begin(), xs.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n\n";

    std::cout << "Output:\n";    
    auto first = xs.begin();
    auto last = xs.end();
    while (first != last)
    {
        //it.first (lower_bound)
        //it.second (upper_bound)
        auto it = std::equal_range(first, last, *first);
        //std::cout << *first << ' ' << (it.second - it.first) << '\n';
        std::cout << *first << ' ' << std::distance(it.first, it.second) << '\n';
        first = it.second; 
    }
}

int main()
{
    seed_rand(now_since_epoch());

    counting_distincts_when_unordered();
    std::cout << "\n";
    counting_distincts_when_ordered();
}
