//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 doubly_linked_list.t.cpp doubly_linked_list.cpp -o doubly_linked_list.exe
//cl /Fo.\obj\ /EHsc /O2 doubly_linked_list.t.cpp doubly_linked_list.cpp /link /out:doubly_linked_list.exe

int doubly_linked_list_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

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
    doubly_linked_list_main(argc, argv, true, true);	
    test_benchmarks(argc, argv);
    return 0;
}