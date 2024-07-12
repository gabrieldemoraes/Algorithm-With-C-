//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 vec2d.cpp -o vec2d.exe
//cl /Fo.\obj\ /EHsc /O2 vec2d.cpp /link /out:vec2d.exe

#include "vec2d.hpp"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <unordered_set>

int main()
{
    vec2d v1(2, 3);
    std::cout << v1[0] << " " << v1[1] << "\n";
    std::cout << v1.operator[](0) << " " << v1.operator[](1) << "\n";
    vec2d v2(2, 3);
    std::cout << std::boolalpha << (v1 == v2) << "\n";
    std::cout << std::boolalpha << (v1 != v2) << "\n";
    v2 += vec2d(1, 1);
    std::cout << v2[0] << " " << v2[1] << "\n";
    vec2d v3 = vec2d(3, 4) + vec2d(5, 6);
    std::cout << v3[0] << " " << v3[1] << "\n";
    vec2d v4 = vec2d(11, 22) * 2;
    std::cout << v4[0] << " " << v4[1] << "\n";
    vec2d v5 = 3 * vec2d(11, 22);
    std::cout << v5[0] << " " << v5[1] << "\n";
    std::cout << std::boolalpha << (vec2d(1, 2) < vec2d(2, 2)) << "\n";
    std::cout << std::boolalpha << (vec2d(2, 2) < vec2d(1, 2)) << "\n";
    std::cout << std::boolalpha << (vec2d(2, 2) < vec2d(2, 2)) << "\n";
    std::cout << std::boolalpha << (vec2d(2, 2) < vec2d(2, 3)) << "\n";
    std::cout << std::boolalpha << (vec2d(1, 2) > vec2d(2, 2)) << "\n";
    std::cout << std::boolalpha << (vec2d(2, 2) > vec2d(1, 2)) << "\n";
    std::cout << std::boolalpha << (vec2d(2, 2) > vec2d(2, 2)) << "\n";
    std::cout << std::boolalpha << (vec2d(2, 2) > vec2d(2, 3)) << "\n";

    std::vector<vec2d> xs;
    xs.push_back(vec2d(3, 5));
    xs.push_back(vec2d(3, 4));
    xs.push_back(vec2d(1, 2));
    xs.push_back(vec2d(2, 2));
    xs.push_back(vec2d(1, 5));
    for (vec2d x : xs)
        std::cout << std::to_string(x) << " ";
    std::cout << "\n";

    std::sort(xs.begin(), xs.end());
    for (vec2d x : xs)
        std::cout << std::to_string(x) << " ";
    std::cout << "\n";

    std::unordered_set<vec2d> ys;
    ys.emplace(vec2d(3, 5));
    ys.emplace(vec2d(3, 4));
    ys.emplace(vec2d(1, 2));
    ys.emplace(vec2d(2, 2));
    ys.emplace(vec2d(1, 5));
    for (vec2d y : ys)
        std::cout << std::to_string(y) << " ";
    std::cout << "\n";

    std::hash<vec2d> vec2d_hasher;
    for (vec2d y : ys)
        std::cout << vec2d_hasher(y) << ":" << std::to_string(y) << " ";

    return 0;
}