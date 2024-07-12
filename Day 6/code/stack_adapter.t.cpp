//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "stack_adapter.hpp"

#include "dynamic_array.hpp"
#include <stack>
#include <string>
#include <iostream>
#include <vector>

namespace stack_adapter
{
    static void test_interactive()
    {
        std::cout << "int: push an item, -: pop an item, ?: display top of stack, !: display info\n";

        //std::stack<int> s;
        //std::stack<int, std::vector<int>> s;
        //std::stack<int, dynamic_array_adapter<int>> s;
        //stack_adapter<int> s;
        //stack_adapter<int, std::vector<int>> s;
        stack_adapter<int, dynamic_array_adapter<int>> s;

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

int stack_adapter_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using stack_adapter::test_interactive;
    
    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}