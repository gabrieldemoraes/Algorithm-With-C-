//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 dynamic_array_lbo.t.cpp dynamic_array_lbo.cpp -o dynamic_array_lbo.exe
//cl /Fo.\obj\ /EHsc /O2 dynamic_array_lbo.t.cpp dynamic_array_lbo.cpp /link /out:dynamic_array_lbo.exe

int dynamic_array_lbo_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

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
    dynamic_array_lbo_main(argc, argv, true, true);
    test_benchmarks(argc, argv);
    return 0;
}