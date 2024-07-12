//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "min_and_max.hpp"
#include "helpers_and_types.hpp"

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <cstddef>

#include "picobench.hpp"

namespace min_and_max
{
    static std::vector<int> get_singleton_test_vector(std::size_t n)
    {
        static std::map<std::size_t, std::vector<int>> dic;
        auto iter = dic.find(n);
        if (iter == dic.end())
        {
            seed_rand(static_cast<unsigned int>(n));
            std::vector<int> xs = generate_random_ints(n, 1, 999999999);
            dic.emplace(n, xs);
            return xs;
        }
        return iter->second;
    }

    static void bench_min(picobench::state& s)
    {
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector(n);

        s.start_timer();
        int _min = min(xs);
        s.stop_timer();

        std::cout << std::setw(8) << n << "            bench_min: " << std::setw(6) << _min << "\n";
    }

    static void bench_max(picobench::state& s)
    {
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector(n);

        s.start_timer();
        int _max = max(xs);
        s.stop_timer();

        std::cout << std::setw(8) << n << "            bench_max: " << std::setw(16) << _max << "\n";
    }

    static void bench_min_then_max(picobench::state& s)
    {
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector(n);
        
        s.start_timer();
        int _min = min(xs);
        int _max = max(xs);
        s.stop_timer();

        std::cout << std::setw(8) << n << "   bench_min_then_max: " << std::setw(6) << _min << " " << std::setw(6) << _max << "\n";
    }

    static void bench_min_max_it(picobench::state& s)
    {
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector(n);

        s.start_timer();
        auto _minmax = min_max_it(xs);
        s.stop_timer();
                                          
        std::cout << std::setw(8) << n << "     bench_min_max_it: " << std::setw(6) << _minmax.first << " " << std::setw(6) << _minmax.second << "\n";		
    }

    static void bench_min_max_idx(picobench::state& s)
    {
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector(n);

        s.start_timer();
        auto _minmax = min_max_idx(xs);
        s.stop_timer();

        std::cout << std::setw(8) << n << "    bench_min_max_idx: " << std::setw(6) << _minmax.first << " " << std::setw(6) << _minmax.second << "\n";
    }

    static void bench_minmax_element(picobench::state& s)
    {
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector(n);

        s.start_timer();
        auto _minmax = std::minmax_element(xs.begin(), xs.end());
        s.stop_timer();
                                  
        std::cout << std::setw(8) << n << " bench_minmax_element: " << std::setw(6) << *_minmax.first << " " << std::setw(6) << *_minmax.second << "\n";
    }

    static void bench_min_and_max(picobench::state& s)
    {
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector(n);

        s.start_timer();
        auto _minmax = min_and_max(xs);
        s.stop_timer();

        std::cout << std::setw(8) << n << "    bench_min_and_max: " << std::setw(6) << _minmax.first << " " << std::setw(6) << _minmax.second << "\n";
    }

    static void register_benchmarks()
    {
        std::vector<int> ITERS{ 2 * 1024 * 1024, 4 * 1024 * 1024, 8 * 1024 * 1024 };
        picobench::global_registry::set_bench_suite("min and max [2 MB, 8 MB]");
        picobench::global_registry::new_benchmark("bench_min", bench_min).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_max", bench_max).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_min_then_max", bench_min_then_max).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_min_max_it", bench_min_max_it).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_min_max_idx", bench_min_max_idx).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_min_and_max", bench_min_and_max).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_minmax_element", bench_minmax_element).iterations(ITERS).baseline();
        
        #ifndef _DEBUG
        std::vector<int> ITERS2{ 16 * 1024 * 1024, 32 * 1024 * 1024, 64 * 1024 * 1024 };
        picobench::global_registry::set_bench_suite("min and max [16 MB, 64 MB]");
        picobench::global_registry::new_benchmark("bench_min", bench_min).iterations(ITERS2);
        picobench::global_registry::new_benchmark("bench_max", bench_max).iterations(ITERS2);
        picobench::global_registry::new_benchmark("bench_min_then_max", bench_min_then_max).iterations(ITERS2);
        picobench::global_registry::new_benchmark("bench_min_max_it", bench_min_max_it).iterations(ITERS2);
        picobench::global_registry::new_benchmark("bench_min_max_idx", bench_min_max_idx).iterations(ITERS2);
        picobench::global_registry::new_benchmark("bench_min_and_max", bench_min_and_max).iterations(ITERS2);
        picobench::global_registry::new_benchmark("bench_minmax_element", bench_minmax_element).iterations(ITERS2).baseline();
        #endif
    }
    
    static void test_stress()
    {
        //seed_rand(1);
        for (std::size_t i = 0; i < 1000; ++i)
        {
            std::vector<int> xs = generate_random_ints(rand_int(1, 1000), 1, 999999);
            int _min = min(xs);
            int _max = max(xs);
            auto _minmax = min_max_it(xs);
            auto _minmax2 = min_max_idx(xs);
            bool match = (_min == _minmax.first) && 
                (_max == _minmax.second) && 
                (_min == _minmax2.first) && 
                (_max == _minmax2.second);
            std::cout << (!match ? "**[" : "  [")
                << "min: " << std::setw(6) << _min << "][" 
                << "max: " << std::setw(6) << _max << "]["
                << "min_max: { min: " << std::setw(6) << _minmax.first << ", "
                << "max: " << std::setw(6) << _minmax.second << " }]["
                << "min_max: { min: " << std::setw(6) << _minmax2.first << ", "
                << "max: " << std::setw(6) << _minmax2.second << " }]\n";
        }
    }

    static void test_interactive()
    {
        std::vector<int> xs;
        int x;
        std::cout << "integer sequence [EOF to stop]:\n";
        while (std::cout << "> ", std::cin >> x)
        {
            xs.push_back(x);
        }
        int _min = min(xs);
        int _max = max(xs);
        //auto _minmax = min_max_it(xs);
        //auto _minmax = min_max_idx(xs);
        auto _minmax = min_and_max(xs);
        bool match = (_min == _minmax.first) && (_max == _minmax.second);
        std::cout << (!match ? "**[" : "  [")
                << "min: " << std::setw(6) << _min << "][" 
                << "max: " << std::setw(6) << _max << "]["
                << "min_max: { min: " << std::setw(6) << _minmax.first << ", "
                << "max: " << std::setw(6) << _minmax.second << " }]\n";
    }
}

int min_and_max_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using min_and_max::test_interactive;
    using min_and_max::test_stress;
    using min_and_max::register_benchmarks;

    if (reg_benchmarks)
    {
        register_benchmarks();
    }

    if (run_tests)
    {
        test_interactive();
        test_stress();
    }

    return 0;
}