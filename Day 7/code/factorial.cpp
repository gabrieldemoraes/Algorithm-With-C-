//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 factorial.cpp -o factorial.exe
//cl /Fo.\obj\ /EHsc /O2 factorial.cpp /link /out:factorial.exe

unsigned int factorial_interactive(unsigned int N)
{
    unsigned int result = 1;
    for (unsigned int i = 2; i <= N; ++i)
        result *=  i;
    return result;
}

unsigned int factorial_recursive(unsigned int N)
{
    //Direct solution
    if (N <= 1)
        return 1;

    //Divide
    unsigned int M = N - 1;

    //Recurse
    unsigned int partial_result = factorial_recursive(M);

    //Combine
    unsigned int result = N * partial_result;

    return result;
    
    //return N * factorial_recursive(N - 1); //Divide, recurse and combine
}

unsigned int factorial_tail_recursive(unsigned int N, unsigned int acc = 1)
{
    if (N <= 1)
        return acc;
    return factorial_tail_recursive(N - 1, N * acc);
}

#include <iostream>

int main()
{
    unsigned int N = 8;
    std::cout << N << "! = " << factorial_interactive(N) << '\n';
    std::cout << N << "! = " << factorial_recursive(N) << '\n';
    std::cout << N << "! = " << factorial_tail_recursive(N) << '\n';

    return 0;
}