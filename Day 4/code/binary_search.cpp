//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 binary_search.t.cpp binary_search.cpp -o binary_search.exe
//cl /Fo.\obj\ /EHsc /O2 binary_search.t.cpp binary_search.cpp /link /out:binary_search.exe

int binary_search_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

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
    binary_search_main(argc, argv, true, true);
    test_benchmarks(argc, argv);
    return 0;
}