//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 benchmarking_algorithms.t.cpp benchmarking_algorithms.cpp -o benchmarking_algorithms.exe
//cl /Fo.\obj\ /EHsc /O2 benchmarking_algorithms.t.cpp benchmarking_algorithms.cpp /link /out:benchmarking_algorithms.exe

int benchmarking_algorithms_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

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
    benchmarking_algorithms_main(argc, argv, false, true);
    test_benchmarks(argc, argv);
    return 0;
}