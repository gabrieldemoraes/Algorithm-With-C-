//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 sorting_insertsort.t.cpp sorting_insertsort.cpp -o sorting_insertsort.exe
//cl /Fo.\obj\ /EHsc /O2 sorting_insertsort.t.cpp sorting_insertsort.cpp /link /out:sorting_insertsort.exe

int sorting_insertsort_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

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
    sorting_insertsort_main(argc, argv, true, true);
    test_benchmarks(argc, argv);
    return 0;
}