//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 substring_searcher.t.cpp substring_searcher.cpp -o substring_searcher.exe
//cl /Fo.\obj\ /EHsc /O2 substring_searcher.t.cpp substring_searcher.cpp /link /out:substring_searcher.exe

int substring_searcher_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

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
    substring_searcher_main(argc, argv, true, true);
    test_benchmarks(argc, argv);
    return 0;
}