//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 kth-largest-element-in-an-array.cpp -o kth-largest-element-in-an-array.exe
//cl /Fo.\obj\ /EHsc /O2  kth-largest-element-in-an-array.cpp /link /out:kth-largest-element-in-an-array.exe

#include <vector>
#include <algorithm>

int find_kth_largest(std::vector<int>& input, int k) 
{
    std::make_heap(input.begin(), input.end());
    auto first = input.begin();
    auto last = input.end();
    while (k-- > 1)
    {
        std::pop_heap(first, last);
        --last;
    }
    return input[0];
}

#include <iostream>

//Test cases:
//6 3 2 1 5 6 4 2
//9 3 2 3 1 2 4 5 5 6 4
//8 1 2 3 4 5 6 7 8 4
//8 1 2 3 4 5 6 7 8 7
//8 1 2 3 4 5 6 7 8 2
int main()
{
    int N, k;
	std::cin >> N;
	std::vector<int> input(N, 0);
	for (int i = 0; i < N; ++i)
		std::cin >> input[i];
    std::cin >> k;

    int kth = find_kth_largest(input, k);
    std::cout << "kth (" << k << ") largest is " << kth << "\n";

    return 0;
}