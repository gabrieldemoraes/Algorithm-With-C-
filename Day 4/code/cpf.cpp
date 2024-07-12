//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 cpf.t.cpp cpf.cpp -o cpf.exe
//cl /Fo.\obj\ /EHsc /O2 cpf.t.cpp cpf.cpp /link /out:cpf.exe

int cpf_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

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
    cpf_main(argc, argv, true, true);
    test_benchmarks(argc, argv);
    return 0;
}