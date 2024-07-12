//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "node_based_stack.hpp"

#include <stack>
#include <string>
#include <iostream>
#include <iomanip>

#include "picobench.hpp"

namespace node_based_stack
{
    static void bench_nb_stack_push(picobench::state& s)
    {
        s.start_timer();
        node_based_stack<int> stk;
        for (int i = 0; i < s.iterations(); ++i)
            stk.push(1 + i);
        s.stop_timer();		             
        std::cout << "node_based_stack<int> size: " << std::setw(8) << stk.size() << "\n";
    }

    static void bench_std_stack_push(picobench::state& s)
    {
        s.start_timer();
        std::stack<int> stk;
        for (int i = 0; i < s.iterations(); ++i)
            stk.push(1 + i);
        s.stop_timer();
        std::cout << "      std::stack<int> size: " << std::setw(8) << stk.size() << "\n";
    }

    static void register_benchmarks()
    {
        picobench::global_registry::set_bench_suite("node_based_stack");
        picobench::global_registry::new_benchmark("bench_nb_stack_push", bench_nb_stack_push);
        picobench::global_registry::new_benchmark("bench_std_stack_push", bench_std_stack_push);
    }

    static void test_interactive()
    {
        std::cout << "int: push an item, -: pop an item, ?: display top of stack, !: display info, EOF: benchmark\n";

        node_based_stack<int> s;

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '-':
                if (!s.empty())
                {
                    s.pop();
                }	
                break;
            case '?':
                if (s.empty())
                {
                    std::cout << "nothing";
                }
                else
                {
                    std::cout << s.top();
                }
                std::cout << "\n";
                break;
            case '!':
                std::cout << "size: " << s.size() << "\n";				
                break;
            default:
                try
                {
                    int x = std::stoi(cmd);
                    s.push(x);
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

int node_based_stack_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using node_based_stack::test_interactive;
    using node_based_stack::register_benchmarks;

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