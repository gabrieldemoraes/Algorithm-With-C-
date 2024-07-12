//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 _demo_bin_packing.cpp -o _demo_bin_packing.exe
//cl /Fo.\obj\ /EHsc /O2 _demo_bin_packing.cpp /link /out:_demo_bin_packing.exe

#include <vector>
#include "_demo_bin.hpp"
#include "unbounded_priority_queue.hpp"

#include <iostream>

int main()
{
    std::vector<int> weights { 5, 3, 4, 3, 2, 1, 5, 5, 1, 1 };

    const int BIN_CAPACITY = 10;
    unbounded_priority_queue::max_pq<Bin> pq;
    pq.insert(Bin(BIN_CAPACITY));

    for (int w : weights)
    {
        if (w < BIN_CAPACITY)
        {
            if (pq.max().size() < w)
                pq.insert(Bin(BIN_CAPACITY));
            Bin b = pq.max();
            pq.remove_max();
            b.try_decrease(w);
            pq.insert(b);
        }
        //else w não cabe no cesto
    }

    std::cout << pq.size() << " Bin(s) of " << BIN_CAPACITY << ":\n";
    for (int i = 1; !pq.empty(); ++i)
    {
        std::cout << i << ": " << pq.max().to_string() << '\n';
        pq.remove_max();
    }

    return 0;
}
