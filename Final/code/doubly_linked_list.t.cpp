//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "doubly_linked_list.hpp"

#include <list>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstddef>

#include "picobench.hpp"

namespace doubly_linked_list
{
    static void bench_append(picobench::state& s)
    {
        s.start_timer();
        doubly_linked_list<int> ll;
        for (int i = 0; i < s.iterations(); ++i)
            append(ll, 1 + i);
        s.stop_timer();
        clear(ll);
        std::cout << "doubly_linked_list<int> size: " << std::setw(8) << count(ll) << "\n";		
    }

    static void bench_push_back(picobench::state& s)
    {
        s.start_timer();
        std::list<int> ll;
        for (int i = 0; i < s.iterations(); ++i)
            ll.push_back(1 + i);
        s.stop_timer();
        std::cout << "         std::list<int> size: " << std::setw(8) << ll.size() << "\n";
    }

    static void register_benchmarks()
    {
        picobench::global_registry::set_bench_suite("doubly_linked_list");
        picobench::global_registry::new_benchmark("bench_append", bench_append);
        picobench::global_registry::new_benchmark("bench_push_back", bench_push_back);
    }
    
    static void test_interactive()
    {
        std::cout << "     int: prepend an item,              +int: append an item\n";
        std::cout << "aint,int: insert after an item,     bint,int: insert before an item\n";
        std::cout << "       -: remove first item,               =: remove last item\n";
        std::cout << "    fint: remove an item (forward),     gint: remove an item (backward)\n";
        std::cout << "       >: display forward,                 <: display backward\n";
        std::cout << "       !: display info,                    c:clear all\n";
        std::cout << "     EOF: benchmark\n";

        doubly_linked_list<int> ll;

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case 'c':
                clear(ll);
                break;
            case '+':
            case 'f':
            case 'g':				
                try
                {
                    int x = std::stoi(cmd.substr(1));
                    if (cmd[0] == 'f')
                        remove_forward(ll, x);
                    else if (cmd[0] == 'g')
                        remove_backward(ll, x);
                    else //+
                        append(ll, x);
                }
                catch (const std::invalid_argument&)
                {
                    std::cout << "input ignored\n";
                }
                break;
            case 'a':
            case 'b':
                try
                {
                    std::size_t pos = cmd.find(',', 1);
                    if (pos == std::string::npos)
                        throw std::invalid_argument("missing ,");
                    int x = std::stoi(cmd.substr(1, pos));
                    int y = std::stoi(cmd.substr(pos + 1));
                    if (cmd[0] == 'a')
                        insert_after(ll, x, y);
                    else //'b'
                        insert_before(ll, x, y);
                }
                catch (const std::invalid_argument&)
                {
                    std::cout << "input ignored\n";
                }				
                break;
            case '-':				
                remove_front(ll);
                break;
            case '=':
                remove_back(ll);
                break;
            case '>':
                std::cout << "_ -> ";
                traverse_forward(ll, [](int x) { std::cout << x << " -> "; });
                std::cout << "_\n";
                break;
            case '<':
                std::cout << "_ -> ";
                traverse_backward(ll, [](int x) { std::cout << x << " -> "; });
                std::cout << "_\n";
                break;
            case '!':
                std::cout << "size: " << count(ll) << "\n";
                break;
            default:
                try
                {
                    int x = std::stoi(cmd);
                    prepend(ll, x);
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

int doubly_linked_list_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using doubly_linked_list::test_interactive;	
    using doubly_linked_list::register_benchmarks;
    
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