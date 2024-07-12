//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "registry.hpp"
#include "helpers_and_types.hpp"

#include <vector>
#include <string>
#include <tuple>
#include <stdexcept>
#include <typeinfo>
#include <iostream>
#include <iomanip>

#include "picobench.hpp"

namespace registry
{
    static void bench_registry_rcca(picobench::state& s)
    {
        registry::russian_coat_check_algorithm_registry<std::string> r;
        int n = s.iterations();
        auto xs = generate_random_strings(n, 6);
        auto x = generate_random_string(6);
        s.start_timer();
        for (std::string& s : xs) r.deposit(s);
        for (int i = 0; i < n; i += 2) r.withdraw(i);
        r.withdraw(1);
        r.deposit(x);
        s.stop_timer();
        std::cout << "russian_coat_check_algorithm_registry size: " << std::setw(8) << r.size() << '\n';
    }

    static void bench_registry_ht(picobench::state& s)
    {
        registry::hash_table_registry<std::string> r;
        int n = s.iterations();
        auto xs = generate_random_strings(n, 6);
        auto x = generate_random_string(6);
        s.start_timer();
        for (std::string& s : xs) r.deposit(s);
        for (int i = 0; i < n; i += 2) r.withdraw(i);
        r.withdraw(1);
        r.deposit(x);
        s.stop_timer();
        std::cout << "                  hash_table_registry size: " << std::setw(8) << r.size() << '\n';
    }

    static void register_benchmarks()
    {
        std::vector<int> ITERS{ 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304 };
        std::vector<int> ITERS2{ 8, 16, 32, 64, 128 };

        picobench::global_registry::set_bench_suite("registry");
        picobench::global_registry::new_benchmark("bench_registry_rcca", bench_registry_rcca).iterations(ITERS).baseline();
        picobench::global_registry::new_benchmark("bench_registry_ht", bench_registry_ht).iterations(ITERS);

        picobench::global_registry::set_bench_suite("registry (few items)");
        picobench::global_registry::new_benchmark("bench_registry_rcca", bench_registry_rcca).iterations(ITERS2).baseline();
        picobench::global_registry::new_benchmark("bench_registry_ht", bench_registry_ht).iterations(ITERS2);
    }

    static void test_interactive()
    {
        std::cout << "string: deposit a string, ?<int>: check a string, -<int>: withdraw a string, !: display info, EOF: benchmark\n";

        registry::russian_coat_check_algorithm_registry<std::string> r;
        //registry::hash_table_registry<std::string> r;

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '-':
                try
                {
                    std::size_t ticket = std::stoi(cmd.substr(1));
                    bool registered; std::string s;
                    std::tie(registered, s) = r.withdraw(ticket);
                    if (registered)
                        std::cout << s << " returned\n";
                    else
                        std::cout << ticket << " not registered\n";
                }
                catch (const std::invalid_argument&)
                {
                    std::cout << "input ignored\n";
                }
                break;
            case '?':
                try
                {
                    std::size_t ticket = std::stoi(cmd.substr(1));
                    bool registered = r.check(ticket);
                    std::cout << ticket << " is" << (registered ? " " : " not ") << "registered\n";
                }
                catch (const std::invalid_argument&)
                {
                    std::cout << "input ignored\n";
                }
                break;
            case '!':
                {
                    std::cout << "    size: " << r.size() << '\n';
                    std::cout << "registry: " << typeid(r).name() << '\n';
                }
                break;
            default:
                {
                    auto ticket = r.deposit(cmd);
                    std::cout << cmd << " deposited and got the ticket #" << ticket << '\n';
                }
                break;
            }
        }
    }
}

int registry_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using registry::test_interactive;
    using registry::register_benchmarks;

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