//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "linear_search.hpp"
#include "helpers_and_types.hpp"

#include <cstddef>
#include <string>
#include <iostream>

#include "dynamic_array.hpp"
#include <vector>
#include <algorithm>

#include "picobench.hpp"

namespace linear_search
{
    static std::vector<std::string> get_singleton_test_vector()
    {
        static std::vector<std::string> xs = generate_random_strings(100, 5);
        return xs;
    }

    static std::string get_target()
    {
        return "?????";
    }

    static void bench_dynarr_add_lsrch(picobench::state& s)
    {
        std::vector<std::string> ys = get_singleton_test_vector();
        dynamic_array::dynamic_array<std::string> xs;
        std::string target = get_target();
        s.start_timer();
        for (int i = 0; i < s.iterations(); ++i)
            xs.add(ys[i % ys.size()]);
        std::size_t pos = linear_search(xs, target);
        if (pos != NOT_FOUND)
            xs.add(target);
        s.stop_timer();
    }

    static void bench_vec_pb_lsrch(picobench::state& s)
    {
        std::vector<std::string> ys = get_singleton_test_vector();
        std::vector<std::string> xs;
        std::string target = get_target();
        s.start_timer();
        for (int i = 0; i < s.iterations(); ++i)
            xs.push_back(ys[i % ys.size()]);
        std::size_t pos = linear_search(xs, target);
        if (pos != NOT_FOUND)
            xs.push_back(target);
        s.stop_timer();
    }

    static void bench_dynarr_add_find(picobench::state& s)
    {
        std::vector<std::string> ys = get_singleton_test_vector();
        dynamic_array::dynamic_array<std::string> xs;
        std::string target = get_target();
        s.start_timer();
        for (int i = 0; i < s.iterations(); ++i)
            xs.add(ys[i % ys.size()]);
        std::string* iter = std::find(xs.begin(), xs.end(), target);
        /*
        std::size_t pos = linear_search_with_sentinel(xs, target);
        std::string* iter = pos != NOT_FOUND ? xs.begin() + pos : xs.end();
        */
        //std::string* iter = linear_search_if(xs.begin(), xs.end(), [&](const std::string& x) { return x == target; });
        //std::string* iter = find_if(xs.begin(), xs.end(), [&](const std::string& x) { return x == target; });
        if (iter == xs.end())
            xs.add(target);
        s.stop_timer();
    }

    static void bench_vec_pb_find(picobench::state& s)
    {
        std::vector<std::string> ys = get_singleton_test_vector();
        std::vector<std::string> xs;
        std::string target = get_target();
        s.start_timer();
        for (int i = 0; i < s.iterations(); ++i)
            xs.push_back(ys[i % ys.size()]);
        std::vector<std::string>::iterator iter = std::find(xs.begin(), xs.end(), target);
        //std::vector<std::string>::iterator iter = linear_search_if(xs.begin(), xs.end(), [&](const std::string& x) { return x == target; });
        //std::vector<std::string>::iterator iter = find_if(xs.begin(), xs.end(), [&](const std::string& x) { return x == target; });
        if (iter == xs.end())
            xs.push_back(target);
        s.stop_timer();
    }
    
    static void register_benchmarks()
    {
        picobench::global_registry::set_bench_suite("linear_search");
        picobench::global_registry::new_benchmark("bench_dynarr_add_lsrch", bench_dynarr_add_lsrch);
        picobench::global_registry::new_benchmark("bench_vec_pb_lsrch", bench_vec_pb_lsrch);
        picobench::global_registry::new_benchmark("bench_dynarr_add_find", bench_dynarr_add_find);
        picobench::global_registry::new_benchmark("bench_vec_pb_find", bench_vec_pb_find);
    }

    static void test_interactive()
    {
        std::size_t n;
        std::cout << "collection size: "; std::cin >> n;
        std::vector<std::string> xs = generate_random_strings(n, 5);		

        std::cout << "string: find an item, ?: display collection, !: display info, EOF: benchmark\n";

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '?':
                if (xs.empty())
                {
                    std::cout << "nothing";
                }
                else
                {
                    for (std::string& x : xs)
                        std::cout << x << " ";
                }
                std::cout << "\n";
                break;
            case '!':
                std::cout << "    size: " << xs.size() << "\n";
                std::cout << "capacity: " << xs.capacity() << "\n";
                std::cout << "   delta: " << xs.capacity() - xs.size() << "\n";
                std::cout << "fst addr: " << (xs.empty() ? 0 : &xs[0]) << "\n";
                break;
            default:
                std::string& x = cmd;
                std::size_t pos = linear_search(xs, x);
                //std::size_t pos = linear_search_with_sentinel(xs, x);
                if (pos != NOT_FOUND)
                {
                    std::cout << "found at " << pos;
                }
                else
                {
                    std::cout << "not found";
                }
                std::cout << "\n";
                break;
            }
        }
    }
}

int linear_search_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using linear_search::test_interactive;
    using linear_search::register_benchmarks;

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