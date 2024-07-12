//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 min_and_max.t.cpp min_and_max.cpp -o min_and_max.exe
//cl /Fo.\obj\ /EHsc /O2 min_and_max.t.cpp min_and_max.cpp /link /out:min_and_max.exe

int min_and_max_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

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
    min_and_max_main(argc, argv, false, true);
    test_benchmarks(argc, argv);
    return 0;
}