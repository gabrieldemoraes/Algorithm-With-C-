//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "bounded_ring_buffer.hpp"

#include <cstddef>
#include <string>
#include <iostream>

#include "memory_allocation.hpp"

namespace bounded_ring_buffer
{
    template <>
    struct bounded_ring_buffer_memory_allocation<int> :
        public memory_allocation::nonconventional_memory_allocation<int>
    {
    };

    static void test_interactive()
    {
        std::size_t size;
        std::cout << "ring buffer size: "; std::cin >> size;
        std::cout << "int: add an item, -: remove an item, ?: display data, !: display info\n";

        bounded_ring_buffer<int> rb(size);

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '-':
            {
                int x;
                if (!rb.pop(x))
                    std::cout << "nothing\n";
            }
            break;
            case '?':
                if (rb.empty())
                {
                    std::cout << "nothing";
                }
                else
                {
                    int x;
                    rb.top(x);
                    std::cout << "top of buffer: " << x << "\n";
                    std::cout << "         data: ";
                    for (std::size_t i = 0; i < rb.size(); ++i)
                    {
                        rb.at(i, x);
                        std::cout << x << " ";
                    }
                }
                std::cout << "\n";
                break;
            case '!':
                std::cout << "capacity: " << rb.capacity() << "\n";
                std::cout << "    size: " << rb.size() << "\n";
                std::cout << "   delta: " << rb.capacity() - rb.size() << "\n";
                break;
            default:
                try
                {
                    int x = std::stoi(cmd);
                    rb.push(x);
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

int bounded_ring_buffer_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using bounded_ring_buffer::test_interactive;

    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}