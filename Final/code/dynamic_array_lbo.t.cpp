//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "dynamic_array_lbo.hpp"

#include <cstddef>
#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>

#include "picobench.hpp"

namespace dynamic_array_lbo
{
    static void bench_dynarr_add(picobench::state& s)
    {
        s.start_timer();
        dynamic_array<int> xs;		
        for (int i = 0; i < s.iterations(); ++i)
            xs.add(1 + i);
        s.stop_timer();
        std::cout << "  dynamic_array<int> size: " << std::setw(8) << xs.size() << " capacity: " << std::setw(8) << xs.capacity() << "\n";
    }
    
    static void bench_std_vec_push_back(picobench::state& s)
    {
        s.start_timer();
        std::vector<int> xs;
        for (int i = 0; i < s.iterations(); ++i)
            xs.push_back(1 + i);
        s.stop_timer();
        std::cout << "         vector<int> size: " << std::setw(8) << xs.size() << " capacity: " << std::setw(8) << xs.capacity() << "\n";
    }
    
    static void bench_std_vec_rsrvd_pb(picobench::state& s)
    {
        s.start_timer();
        std::vector<int> xs;
        xs.reserve(s.iterations());
        for (int i = 0; i < s.iterations(); ++i)
            xs.push_back(1 + i);
        s.stop_timer();
        std::cout << "reserved vector<int> size: " << std::setw(8) << xs.size() << " capacity: " << std::setw(8) << xs.capacity() << "\n";
    }

    static void bench_dynarr_small_add(picobench::state& s)
    {
        s.start_timer();
        dynamic_array<int> xs(8);		
        for (int i = 1; i <= s.iterations(); ++i)
        {
            xs.add(i);
            if (i % 8 == 0)
                xs.clear();
        }
        s.stop_timer();
        std::cout << "  dynamic_array<int> size: " << std::setw(8) << xs.size() << " capacity: " << std::setw(8) << xs.capacity() << "\n";
    }
    
    static void bench_std_vec_sm_rsv_pb(picobench::state& s)
    {
        s.start_timer();
        std::vector<int> xs;
        xs.reserve(8);
        for (int i = 1; i <= s.iterations(); ++i)
        {
            xs.push_back(i);
            if (i % 8 == 0)
                xs.clear();
        }
        s.stop_timer();
        std::cout << "reserved vector<int> size: " << std::setw(8) << xs.size() << " capacity: " << std::setw(8) << xs.capacity() << "\n";
    }

    static void bench_dynarr_heap_add(picobench::state& s)
    {
        const int K = s.iterations() / 2;
        s.start_timer();
        dynamic_array<int> xs(8);
        for (int i = 1; i <= s.iterations(); ++i)
        {
            xs.add(i);
            if (i == K)
                for (int j = 0; j < K; ++j)
                    xs.remove();            
        }
        s.stop_timer();
        std::cout << "  dynamic_array<int> size: " << std::setw(8) << xs.size() << " capacity: " << std::setw(8) << xs.capacity() << "\n";
    }

    static void bench_std_vec_heap_pb(picobench::state& s)
    {
        const int K = s.iterations() / 2;
        s.start_timer();
        std::vector<int> xs;
        for (int i = 1; i <= s.iterations(); ++i)
        {
            xs.push_back(i);
            if (i == K)
                for (int j = 0; j < K; ++j)
                    xs.pop_back();
        }
        s.stop_timer();
        std::cout << "         vector<int> size: " << std::setw(8) << xs.size() << " capacity: " << std::setw(8) << xs.capacity() << "\n";
    }

    static void bench_std_vec_hp_rsv_pb(picobench::state& s)
    {
        const int K = s.iterations() / 2;
        s.start_timer();
        std::vector<int> xs;
        xs.reserve(8);
        for (int i = 1; i <= s.iterations(); ++i)
        {
            xs.push_back(i);
            if (i == K)
                for (int j = 0; j < K; ++j)
                    xs.pop_back();
        }
        s.stop_timer();
        std::cout << "reserved vector<int> size: " << std::setw(8) << xs.size() << " capacity: " << std::setw(8) << xs.capacity() << "\n";
    }

    static void register_benchmarks()
    {
        std::vector<int> ITERS{ 32768, 65536, 131072, 262144, 524288, 1048576 };
        
        picobench::global_registry::set_bench_suite("dynamic_array");
        picobench::global_registry::new_benchmark("bench_dynarr_add", bench_dynarr_add).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_std_vec_push_back", bench_std_vec_push_back).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_std_vec_rsrvd_pb", bench_std_vec_rsrvd_pb).iterations(ITERS).baseline();

        picobench::global_registry::set_bench_suite("dynamic_array small (only on stack)");
        picobench::global_registry::new_benchmark("bench_dynarr_small_add", bench_dynarr_small_add).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_std_vec_sm_rsv_pb", bench_std_vec_sm_rsv_pb).iterations(ITERS).baseline();

        std::vector<int> ITERS2{ 1 << 5, 1 << 6, 1 << 7, 1 << 8, 1 << 9, 1 << 10 };
        
        picobench::global_registry::set_bench_suite("dynamic_array lbo (on stack or on heap)");
        //picobench::global_registry::new_benchmark("bench_std_vec_heap_pb", bench_std_vec_heap_pb).iterations(ITERS2);
        picobench::global_registry::new_benchmark("bench_dynarr_heap_add", bench_dynarr_heap_add).iterations(ITERS2);        
        picobench::global_registry::new_benchmark("bench_std_vec_hp_rsv_pb", bench_std_vec_hp_rsv_pb).iterations(ITERS2).baseline();
    }
    
    static void test_interactive()
    {
        std::cout << "int: add an item, -: remove an item, @: clear all, ?: display data, !: display info, EOF: benchmark\n";

        dynamic_array<int> xs;
        
        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '-':
                try
                {
                    xs.remove();
                }
                catch (std::runtime_error& err)
                {
                    std::cout << err.what() << '\n';
                }
                break;
            case '?':
                if (xs.empty())
                {
                    std::cout << "nothing";
                }
                else
                {
                    for (std::size_t i = 0; i < xs.size(); ++i)
                        std::cout << xs[i] << ' ';
                }
                std::cout << '\n';
                break;
            case '@':
                xs.clear();
                std::cout << "cleared\n";
                break;
            case '!':
                std::cout << "    size: " << xs.size() << '\n';
                std::cout << "capacity: " << xs.capacity() << '\n';
                std::cout << "   delta: " << xs.capacity() - xs.size() << '\n';
                std::cout << "fst addr: " << (xs.empty() ? 0 : &xs[0]) << '\n';
                std::cout << "in stack: " << std::boolalpha << xs.is_data_on_stack() << '\n';
                break;
            default:
                try
                {
                    int x = std::stoi(cmd);
                    try
                    {
                        xs.add(x);
                    }
                    catch (std::bad_alloc& err)
                    {
                        std::cout << err.what() << '\n';
                    }
                }
                catch (const std::invalid_argument&)
                {
                    std::cout << "input ignored\n";
                }				
                break;
            }
        }
    }
}

int dynamic_array_lbo_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using dynamic_array_lbo::test_interactive;
    using dynamic_array_lbo::register_benchmarks;

    if (reg_benchmarks)
    {
        register_benchmarks();
    }

    if (run_tests)
    {
        test_interactive();
    }
    
    return 0;
}