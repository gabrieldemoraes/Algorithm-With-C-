//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#define PICOBENCH_IMPLEMENT
#include "picobench.hpp"

int run_benchmark(int argc, char* argv[])
{
    picobench::runner runner;
    runner.parse_cmd_line(argc, argv);
    return runner.run();
}

void bench_func_1(picobench::state& s)
{
    //... initialization
    
    //... time it
    s.start_timer();
    for (int i = 0; i < s.iterations(); ++i)
    {
        //... code
    }
    s.stop_timer();
    
    //... finalization
}

void bench_func_2(picobench::state& s)
{
    //... initialization
    
    //... time it
    s.start_timer();
    for (int i = 0; i < s.iterations(); ++i)
    {
        //... code
    }
    s.stop_timer();
    
    //... finalization
}

void register_benchmarks()
{
    std::vector<int> ITERS { 1 << 10, 1 << 11, 1 << 12, 1 << 13, 1 << 14, 1 << 15 };
    picobench::global_registry::set_bench_suite("bench_funcs");
    picobench::global_registry::new_benchmark("bench_func_1", bench_func_1).iterations(ITERS);
    picobench::global_registry::new_benchmark("bench_func_2", bench_func_2).iterations(ITERS);
}

int main(int argc, char* argv[])
{
    register_benchmarks();
    return run_benchmark(argc, argv);
}