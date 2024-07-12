//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "unbounded_heap.hpp"
#include "helpers_and_types.hpp"

#include <cstddef>
#include <string>
#include <iostream>

namespace unbounded_heap
{
    static void test_interactive_max_heap()
    {
        std::size_t size;
        std::cout << "max heap initial size of random ints: "; std::cin >> size;
        std::cout << "int: add an item, -: remove max item, ?: display data, !: display info\n";

        unbounded_max_heap<int> h(generate_random_ints(size, 1, 100));

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '-':
            {
                int x;
                if (!h.pop(x))
                    std::cout << "nothing\n";
            }
            break;
            case '?':
                if (h.empty())
                {
                    std::cout << "nothing";
                }
                else
                {
                    int x;
                    h.top(x);
                    std::cout << "top of heap: " << x << "\n";
                    std::cout << "       data: ";
                    for (std::size_t i = 0; i < h.size(); ++i)
                    {
                        h.at(i, x);
                        std::cout << x << " ";
                    }
                }
                std::cout << "\n";
                break;
            case '!':
                std::cout << "size: " << h.size() << "\n";
                break;
            default:
                try
                {
                    int x = std::stoi(cmd);
                    h.push(x);
                }
                catch (const std::invalid_argument&)
                {
                    std::cout << "input ignored\n";
                }
                break;
            }
        }
    }

    static void test_interactive_min_heap()
    {
        std::size_t size;
        std::cout << "min heap initial size of random ints: "; std::cin >> size;
        std::cout << "int: add an item, -: remove min item, ?: display data, !: display info\n";

        unbounded_min_heap<int> h(generate_random_ints(size, 1, 100));

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '-':
            {
                int x;
                if (!h.pop(x))
                    std::cout << "nothing\n";
            }
            break;
            case '?':
                if (h.empty())
                {
                    std::cout << "nothing";
                }
                else
                {
                    int x;
                    h.top(x);
                    std::cout << "top of heap: " << x << "\n";
                    std::cout << "       data: ";
                    for (std::size_t i = 0; i < h.size(); ++i)
                    {
                        h.at(i, x);
                        std::cout << x << " ";
                    }
                }
                std::cout << "\n";
                break;
            case '!':
                std::cout << "size: " << h.size() << "\n";
                break;
            default:
                try
                {
                    int x = std::stoi(cmd);
                    h.push(x);
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

int unbounded_heap_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using unbounded_heap::test_interactive_max_heap;
    using unbounded_heap::test_interactive_min_heap;

    if (run_tests)
    {
        test_interactive_max_heap();
        //test_interactive_min_heap();
    }

    return 0;
}