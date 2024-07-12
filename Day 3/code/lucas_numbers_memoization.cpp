//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 lucas_numbers_memoization.t.cpp lucas_numbers_memoization.cpp -o lucas_numbers_memoization.exe
//cl /Fo.\obj\ /EHsc /O2 lucas_numbers_memoization.t.cpp lucas_numbers_memoization.cpp /link /out:lucas_numbers_memoization.exe

int lucas_numbers_memoization_main(int argc, char *argv[], bool run);

#define PICOBENCH_DEFAULT_ITERATIONS {1000, 10000, 100000, 1000000}
#define PICOBENCH_IMPLEMENT
#include "picobench.hpp"

static int test_benchmarks(int argc, char *argv[])
{
    picobench::runner runner;
    runner.parse_cmd_line(argc, argv);
    return runner.run();
}

int main(int argc, char *argv[])
{
    lucas_numbers_memoization_main(argc, argv, true);
    test_benchmarks(argc, argv);
    return 0;
}