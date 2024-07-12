//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 node_based_stack.t.cpp node_based_stack.cpp -o node_based_stack.exe
//cl /Fo.\obj\ /EHsc /O2 node_based_stack.t.cpp node_based_stack.cpp /link /out:node_based_stack.exe

int node_based_stack_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

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
    node_based_stack_main(argc, argv, true, true);	
    test_benchmarks(argc, argv);
    return 0;
}