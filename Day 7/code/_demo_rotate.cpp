//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 _demo_rotate.cpp -o _demo_rotate.exe
//cl /Fo.\obj\ /EHsc /O2 _demo_rotate.cpp /link /out:_demo_rotate.exe

#include "helpers_and_types.hpp"

#include <vector>
#include <algorithm>
#include <iostream>

void test_rotate(std::vector<int> ints, std::size_t new_first_point, std::size_t until_point = -1)
{
    std::cout << " input: ";
    for(int i : ints) std::cout << i << ' ';
    std::cout << '\n';
    
    std::rotate(ints.begin(), ints.begin() + new_first_point, until_point == -1 ? ints.end() : ints.begin() + until_point);

    std::cout << "output: ";
    for(int i : ints) std::cout << i << ' ';
    std::cout << "\n\n";
}

int main()
{
    seed_rand(now_since_epoch());
    
    test_rotate(generate_random_ints(10, 1, 9), 5);
    test_rotate(generate_random_ints(10, 1, 9), 5, 6);

    std::vector<int> ints = generate_random_ints(10, 1, 9);
    
    std::cout << " input: ";
    for(int i : ints) std::cout << i << ' ';
    std::cout << '\n';
    
    //std::rotate(ints.begin(), ints.begin() + 5, ints.end());
    //std::rotate(ints.begin() + 1, ints.begin() + 5, ints.end());
    std::rotate(ints.begin() + 2, ints.begin() + 5, ints.begin() + 6);

    std::cout << "output: ";
    for(int i : ints) std::cout << i << ' ';    

    return 0;
}