//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 benchmark_linear_search.cpp -o benchmark_linear_search.exe
//cl /Fo.\obj\ /EHsc /O2 benchmark_linear_search.cpp /link /out:benchmark_linear_search.exe

#include "helpers_and_types.hpp"

#define PICOBENCH_IMPLEMENT
#include "picobench.hpp"

int run_benchmark(int argc, char* argv[])
{
    picobench::runner runner;
    runner.parse_cmd_line(argc, argv);
    return runner.run();
}

#include <cstddef>
#include <vector>
#include <iostream>

const std::size_t NOT_FOUND = -1;

std::size_t linear_search(std::vector<int>& xs, int target)
{
    if (xs.size() == 0)
        return NOT_FOUND;

    for (std::size_t i = 0, l = xs.size(); i < l; ++i)
        if (xs[i] == target)
            return i;
    return NOT_FOUND;
}

std::size_t linear_search_with_sentinel(std::vector<int>& xs, int target)
{
    if (xs.size() == 0)
        return NOT_FOUND;

    std::size_t i = 0, n = xs.size() - 1;
    int last = xs[n];
    xs[n] = target; //sentinel
    while (xs[i] != target)
        ++i;
    xs[n] = last;
    if (i < n || xs[n] == target)
        return i;
    return NOT_FOUND;
}

std::vector<int>& get_singleton_test_vector()
{
    static std::vector<int> xs = generate_random_ints(1000000, 1, 1000);
    return xs;
}

void bench_vec_lsrch(picobench::state& s)
{
    //... initialization
    std::vector<int>& xs = get_singleton_test_vector();
    //int target = 42;
    int target = 1001;
    s.start_timer();
    std::size_t pos = linear_search(xs, target);
    s.stop_timer();
    //... finalization
    std::cout << s.iterations() << ' ' << target << ' ' << pos << '\n';
}

void bench_vec_lsrch_ws(picobench::state& s)
{
    //... initialization
    std::vector<int>& xs = get_singleton_test_vector();
    //int target = 42;
    int target = 1001;
    s.start_timer();
    std::size_t pos = linear_search_with_sentinel(xs, target);
    s.stop_timer();
    //... finalization
    std::cout << s.iterations() << ' ' << target << ' ' << pos << '\n';
}

void register_benchmarks()
{
    std::vector<int> ITERS { 1 << 10, 1 << 11, 1 << 12, 1 << 13, 1 << 14, 1 << 15 };
    picobench::global_registry::set_bench_suite("linear_search");
    picobench::global_registry::new_benchmark("bench_vec_lsrch", bench_vec_lsrch).iterations(ITERS);
    picobench::global_registry::new_benchmark("bench_vec_lsrch_ws", bench_vec_lsrch_ws).iterations(ITERS);
}

int main(int argc, char* argv[])
{
    get_singleton_test_vector();
    register_benchmarks();
    return run_benchmark(argc, argv);
}