//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 stock_prices_max_profit.t.cpp stock_prices_max_profit.cpp -o stock_prices_max_profit.exe
//cl /Fo.\obj\ /EHsc /O2 stock_prices_max_profit.t.cpp stock_prices_max_profit.cpp /link /out:stock_prices_max_profit.exe

int stock_prices_max_profit_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks);

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
    stock_prices_max_profit_main(argc, argv, true, true);	
    test_benchmarks(argc, argv);
    return 0;
}