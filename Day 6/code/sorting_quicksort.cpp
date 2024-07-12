//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 sorting_quicksort.t.cpp sorting_quicksort.cpp -o sorting_quicksort.exe
//cl /Fo.\obj\ /EHsc /O2 sorting_quicksort.t.cpp sorting_quicksort.cpp /link /out:sorting_quicksort.exe

int sorting_quicksort_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

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
    sorting_quicksort_main(argc, argv, true, true);
    test_benchmarks(argc, argv);
    return 0;
}