//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "bounded_queue.hpp"

#include <cstddef>
#include <string>
#include <iostream>

#include "memory_allocation.hpp"

namespace bounded_queue
{
    template <>
    struct bounded_queue_memory_allocation<int> :
        public memory_allocation::nonconventional_memory_allocation<int>
    {
    };

    static void test_interactive()
    {
        std::size_t size;
        std::cout << "queue size: "; std::cin >> size;
        std::cout << "int: enqueue an item, -: dequeue an item, ?: display data, !: display info\n";

        bounded_queue<int> q(size);

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '-':
            {
                int x;
                if (!q.pop(x))
                    std::cout << "nothing\n";
            }
            break;
            case '?':
                if (q.empty())
                {
                    std::cout << "nothing";
                }
                else
                {
                    int x;
                    q.top(x);
                    std::cout << "top of queue: " << x << "\n";
                    std::cout << "        data: ";
                    for (std::size_t i = 0; i < q.size(); ++i)
                    {
                        q.at(i, x);
                        std::cout << x << " ";
                    }
                }
                std::cout << "\n";
                break;
            case '!':
                std::cout << "capacity: " << q.capacity() << "\n";
                std::cout << "    size: " << q.size() << "\n";
                std::cout << "   delta: " << q.capacity() - q.size() << "\n";
                break;
            default:
                try
                {
                    int x = std::stoi(cmd);
                    if (!q.push(x))
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

int bounded_queue_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using bounded_queue::test_interactive;

    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}