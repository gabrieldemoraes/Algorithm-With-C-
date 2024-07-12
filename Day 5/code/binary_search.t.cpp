//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "binary_search.hpp"
#include "helpers_and_types.hpp"

#include <cstddef>
#include <string>
#include <iostream>

#include "dynamic_array.hpp"
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iterator>

#include "picobench.hpp"

namespace binary_search
{
    static std::vector<std::string> get_singleton_test_vector(std::size_t n)
    {
        static std::map<std::size_t, std::vector<std::string>> dic;
        auto iter = dic.find(n);
        if (iter == dic.end())
        {
            std::vector<std::string> xs = generate_ordered_random_strings(n, 5);
            dic.emplace(n, xs);
            return xs;
        }
        return iter->second;
    }

    static std::string get_target()
    {
        return "?????";
    }

    static void bench_vec_pb_binsrch(picobench::state& s)
    {
        std::vector<std::string> ys = get_singleton_test_vector(s.iterations());
        std::vector<std::string> xs;
        std::string target = get_target();
        auto compare = [](const std::string& lhs, const std::string& rhs) { return lhs.compare(rhs); };
        s.start_timer();		
        for (int i = 0; i < s.iterations(); ++i)
            xs.push_back(ys[i]);
        std::size_t pos = binary_search(xs, target, compare);
        if (pos != NOT_FOUND)
            xs.push_back(target);
        s.stop_timer();
    }

    static void bench_vec_pb_std_bsrch(picobench::state& s)
    {
        std::vector<std::string> ys = get_singleton_test_vector(s.iterations());
        std::vector<std::string> xs;
        std::string target = get_target();
        auto compare = [](const std::string& lhs, const std::string& rhs) { return lhs.compare(rhs); };
        s.start_timer();
        for (int i = 0; i < s.iterations(); ++i)
            xs.push_back(ys[i]);
        bool found = std::binary_search(xs.begin(), xs.end(), target);
        if (!found)
            xs.push_back(target);
        s.stop_timer();
    }

    static void bench_std_bsrch(picobench::state& s)
    {
        std::vector<std::string> xs = get_singleton_test_vector(s.iterations());
        std::string target = get_target();
        s.start_timer();
        for (int i = 0, l = s.iterations() / 4; i < l; ++i)
        {
            xs.pop_back();
            bool found = std::binary_search(xs.begin(), xs.end(), target);
            if (!found)
                xs.push_back(target);
        }
        s.stop_timer();
    }

    static void bench_std_find(picobench::state& s)
    {
        std::vector<std::string> xs = get_singleton_test_vector(s.iterations());
        std::string target = get_target();
        s.start_timer();
        for (int i = 0, l = s.iterations() / 4; i < l; ++i)
        {
            xs.pop_back();
            bool found = std::find(xs.begin(), xs.end(), target) != xs.end();
            if (!found)
                xs.push_back(target);
        }
        s.stop_timer();
    }

    static void bench_dynarr_std_lwr_bd(picobench::state& s)
    {
        std::vector<std::string> ys = get_singleton_test_vector(s.iterations());
        dynamic_array::dynamic_array<std::string> xs(ys.size());
        for (std::string y : ys) xs.add(std::move(y));
        std::string target = get_target();
        s.start_timer();
        for (int i = 0, l = s.iterations() / 4; i < l; ++i)
        {
            xs.remove();
            bool found = std::lower_bound(xs.begin(), xs.end(), target) != xs.end();
            if (!found)
                xs.add(target);
        }
        s.stop_timer();
    }

    static void bench_dynarr_std_upr_bd(picobench::state& s)
    {
        std::vector<std::string> ys = get_singleton_test_vector(s.iterations());
        dynamic_array::dynamic_array<std::string> xs(ys.size());
        for (std::string y : ys) xs.add(std::move(y));
        std::string target = get_target();
        s.start_timer();
        for (int i = 0, l = s.iterations() / 4; i < l; ++i)
        {
            xs.remove();
            bool found = std::upper_bound(xs.begin(), xs.end(), target) != xs.end();
            if (!found)
                xs.add(target);
        }
        s.stop_timer();
    }

    static void bench_vec_between(picobench::state& s)
    {
        std::vector<std::string> xs = get_singleton_test_vector(s.iterations());
        std::string lhs = xs[xs.size() / 4], rhs = xs[xs.size() / 2];
        xs.push_back("?????"); xs.push_back("?????");		
        std::vector<std::size_t> ranges;
        s.start_timer();
        for (int i = 0, l = s.iterations() / 4; i < l; ++i)
        {
            xs.pop_back(); xs.pop_back();
            auto range = between(xs, lhs, rhs);
            xs.push_back(*std::get<0>(range));
            xs.push_back(*std::get<1>(range));
        }
        s.stop_timer();
    }

    static void bench_dynarr_between(picobench::state& s)
    {
        std::vector<std::string> ys = get_singleton_test_vector(s.iterations());
        dynamic_array::dynamic_array<std::string> xs(ys.size());
        for (std::string y : ys) xs.add(std::move(y));
        std::string lhs = xs[xs.size() / 4], rhs = xs[xs.size() / 2];
        xs.add("?????"); xs.add("?????");
        std::vector<std::size_t> ranges;
        s.start_timer();
        for (int i = 0, l = s.iterations() / 4; i < l; ++i)
        {
            xs.remove(); xs.remove();
            auto range = between(xs, lhs, rhs);
            xs.add(*std::get<0>(range));
            xs.add(*std::get<1>(range));
        }
        s.stop_timer();
    }

    static void register_benchmarks()
    {
        std::vector<int> ITERS{ 2048, 4096, 8192, 16384 };

        picobench::global_registry::set_bench_suite("binary_search");
        picobench::global_registry::new_benchmark("bench_vec_pb_binsrch", bench_vec_pb_binsrch).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_vec_pb_std_bsrch", bench_vec_pb_std_bsrch).iterations(ITERS);
        
        picobench::global_registry::set_bench_suite("std::binary_search versus std::find");
        picobench::global_registry::new_benchmark("bench_std_bsrch", bench_std_bsrch).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_std_find", bench_std_find).iterations(ITERS);

        picobench::global_registry::set_bench_suite("dynamic_array and binary_search");
        picobench::global_registry::new_benchmark("bench_dynarr_std_lwr_bd", bench_dynarr_std_lwr_bd).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_dynarr_std_upr_bd", bench_dynarr_std_upr_bd).iterations(ITERS);

        picobench::global_registry::set_bench_suite("between");
        picobench::global_registry::new_benchmark("bench_vec_between", bench_vec_between).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_dynarr_between", bench_dynarr_between).iterations(ITERS);
    }

    static void test_interactive()
    {
        std::size_t n;
        std::cout << "collection size: "; std::cin >> n;
        std::vector<std::string> xs = generate_random_strings(n, 5);
        for (int i = 0; i < 4; ++i) { xs.push_back("AAAAA"); xs.push_back("MMMMM"); } //force repeated strings
        std::sort(xs.begin(), xs.end());

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
                std::cout << "leftmost (1), rightmost (2), first match (0, 3, ...)? ";
                int bs_match; std::cin >> bs_match;
                std::string& x = cmd;
                auto compare = [](const std::string& lhs, const std::string& rhs) { return lhs.compare(rhs); };
                std::size_t pos =
                    bs_match == 1 ? binary_search_leftmost(xs, x, compare) :
                    bs_match == 2 ? binary_search_rightmost(xs, x, compare) :
                    binary_search(xs, x, compare);
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

    static void test_interactive_with_ints()
    {
        std::size_t n;
        std::cout << "collection max size: "; std::cin >> n;
        std::vector<int> xs = generate_ordered_distinct_random_ints(n, 1, 2 * static_cast<int>(n));
        
        std::cout << "int: find an item, ?: display collection, !: display info, EOF: benchmark\n";

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
                    for (int x : xs)
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
                try
                {
                    int x = std::stoi(cmd);
                    auto compare = [](int lhs, int rhs) { return lhs - rhs; };
                    std::size_t pos = binary_search(xs, x, compare);
                    //std::vector<int>::iterator bound = std::lower_bound(xs.begin(), xs.end(), x);
                    //std::size_t pos = (*bound == x) ? bound - xs.begin() : NOT_FOUND;
                    if (pos != NOT_FOUND)
                    {
                        std::cout << "found at " << pos;
                    }
                    else
                    {
                        std::cout << "not found";
                    }
                    std::cout << "\n";
                    
                }
                catch (const std::invalid_argument&)
                {
                    std::cout << "input ignored\n";
                }
                break;
            }
        }
    }

    static void test_interactive_with_range()
    {
        std::size_t n;
        std::cout << "collection size: "; std::cin >> n;
        std::vector<int> xs = generate_ordered_random_ints(n, 1, static_cast<int>(n) / 2);

        std::cout << "int: find equals, int,int: find between, ?: display collection, !: display info, EOF: benchmark\n";

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
                    for (int x : xs)
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
                try
                {
                    using iter_type = typename std::vector<int>::const_iterator;
                    std::tuple<iter_type, iter_type> range;
                    std::size_t pos = cmd.find(',');
                    if (pos == std::string::npos)
                    {
                        int x = std::stoi(cmd);
                        range = equal_range(xs, x);
                    }
                    else
                    {
                        int x = std::stoi(cmd.substr(0, pos));
                        int y = std::stoi(cmd.substr(pos + 1));
                        range = between(xs, x, y);
                    }
                    
                    auto first = std::get<0>(range);
                    auto last = std::get<1>(range);
                    if (distance(first, last) > 0)
                    {
                        auto begin = xs.cbegin();
                        std::cout << "found at [" 
                            << std::distance(begin, first) << ", " 
                            << std::distance(begin, last) << ")\n";
                        for (auto iter = first; iter != last; ++iter)
                            std::cout << *iter << " ";
                    }
                    else
                    {
                        std::cout << "not found";
                    }
                    std::cout << "\n";
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

int binary_search_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using binary_search::test_interactive;
    using binary_search::test_interactive_with_ints;
    using binary_search::test_interactive_with_range;
    using binary_search::register_benchmarks;

    if (reg_benchmarks)
    {
        register_benchmarks();
    }

    if (run_tests)
    {
        //test_interactive_with_ints();
        //test_interactive();
        test_interactive_with_range();
    }

    return 0;
}