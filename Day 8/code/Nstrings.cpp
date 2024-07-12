//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 NStrings.cpp -o NStrings.exe
//cl /Fo.\obj\ /EHsc /O2 NStrings.cpp /link /out:NStrings.exe

//Examples:
//NStrings.exe 1024 4 4 > blocklist1.txt
//NStrings 512 4 4 > blocklist-targets1.txt
//NStrings.exe 10240 4 4 > blocklist2.txt
//NStrings 2048 4 4 > blocklist-targets2.txt
//NStrings 131072 4 4 > blocklist3.txt
//NStrings 32768 4 4 > blocklist-targets3.txt
//NStrings 524288 4 4 > blocklist4.txt
//NStrings 32768 4 4 > blocklist-targets4.txt

#include "helpers_and_types.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char *argv[])
{
    seed_rand(now_since_epoch());	
    auto N = argc > 1 ? std::stoi(argv[1]) : rand_int(10, 100);
    auto m = argc > 2 ? std::stoi(argv[2]) : rand_int(2, 4);
    auto M = argc > 3 ? std::stoi(argv[3]) : rand_int(4, 6);
    std::vector<std::string> strings = generate_random_strings(N, m, M);
    std::cerr << strings.size() << "\n";
    for (auto s : strings)
        std::cout << s << "\n";
    return 0;
}