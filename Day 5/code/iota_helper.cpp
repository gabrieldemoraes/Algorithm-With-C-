//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 iota_helper.cpp -o iota_helper.exe
//cl /Fo.\obj\ /EHsc /O2 iota_helper.cpp /link /out:iota_helper.exe

#include "iota_helper.hpp"

#include <numeric>
#include <vector>
#include <forward_list>
#include <iterator>
#include <algorithm>
#include <iostream>

template <class InputIterator>
void display(InputIterator first, InputIterator last)
{
    std::copy(first, last, std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}

int main(int argc, char *argv[])
{
    std::vector<long> xs(25, 0);
    std::forward_list<long> ys(25, 0);
    
    std::iota(xs.begin(), xs.end(), 10);
    std::iota(ys.begin(), ys.end(), 20);

    display(xs.begin(), xs.end());
    display(ys.begin(), ys.end());

    std::iota(xs.begin(), xs.end(), iota_helper::iota_step(10, 2));
    std::iota(ys.begin(), ys.end(), iota_helper::iota_step(20, 3));

    display(xs.begin(), xs.end());
    display(ys.begin(), ys.end());

    std::iota(xs.begin(), xs.end(), iota_helper::iota_random(11, 99));
    std::iota(ys.begin(), ys.end(), iota_helper::iota_random(22, 88));

    display(xs.begin(), xs.end());
    display(ys.begin(), ys.end());
}