//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "bounded_stack.hpp"

#include <cstddef>
#include <string>
#include <iostream>

#include "memory_allocation.hpp"

namespace bounded_stack
{
    template <>
    struct bounded_stack_memory_allocation<int> :
        public memory_allocation::nonconventional_memory_allocation<int>
    {
    };

    static void test_interactive()
    {
        std::size_t size;
        std::cout << "stack size: "; std::cin >> size;
        std::cout << "int: push an item, -: pop an item, ?: display data, !: display info, r: resize\n";

        bounded_stack<int> s(size);

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case 'r':
                {
                    std::size_t new_size;
                    std::cout << "stack new size: "; std::cin >> new_size;
                    s = std::move(resize(s, new_size));
                }
                break;
            case '-':
                {
                    int x;
                    if (!s.pop(x))
                        std::cout << "nothing\n";
                }	
                break;
            case '?':
                if (s.empty())
                {
                    std::cout << "nothing";
                }
                else
                {
                    int x;
                    s.top(x);
                    std::cout << "top of stack: " << x << "\n";
                    std::cout << "        data: ";
                    for (std::size_t i = 0; i < s.size(); ++i)
                    {
                        s.at(i, x);
                        std::cout << x << " ";
                    }
                }
                std::cout << "\n";
                break;
            case '!':
                std::cout << "capacity: " << s.capacity() << "\n";
                std::cout << "    size: " << s.size() << "\n";
                std::cout << "   delta: " << s.capacity() - s.size() << "\n";				
                break;
            default:
                try
                {
                    int x = std::stoi(cmd);
                    if (!s.push(x))
                        std::cout << "full\n";
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

int bounded_stack_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using bounded_stack::test_interactive;
    
    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}