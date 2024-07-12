//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "linear_probing_hashtable.hpp"
#include "helpers_and_types.hpp"

#include <cstddef>
#include <string>
#include <iostream>

namespace linear_probing_hashtable
{
    static void test_interactive()
    {
        dictionary<std::string, std::string> d;

        std::cout << "string: find value by key,     string,string: add or update key and value\n";
        std::cout << "     ?: display collection,                !: display info\n";
        std::cout << "   int: insert random keys and values\n";

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '?':
                {
                    if (d.empty())
                    {
                        std::cout << "nothing";
                    }
                    else
                    {
                        for (std::string& k : d.keys())
                        {
                            std::string v; d.get(k, v);
                            std::cout << k << ":" << v << " ";
                        }
                    }
                    std::cout << "\n";
                }
                break;
            case '!':
                {
                    std::cout << "    size: " << d.size() << "\n";
                    std::cout << "capacity: " << d.capacity() << "\n";
                    std::cout << "   delta: " << d.capacity() - d.size() << "\n";
                }
                break;
            default:
                {
                    using iter_type = typename std::vector<int>::const_iterator;
                    std::tuple<iter_type, iter_type> range;
                    std::size_t pos = cmd.find(',');
                    if (pos == std::string::npos)
                    {
                        try
                        {
                            //insert n randomly
                            int n = std::stoi(cmd);
                            for (int i = 0; i < n; ++i)
                            {
                                std::string k = generate_random_string(5);
                                std::string v = generate_random_string(5);
                                d.add_or_update(k, v);
                            }							
                        }
                        catch (const std::invalid_argument&)
                        {
                            //find by key
                            std::string& k = cmd;
                            std::string v;
                            if (d.get(k, v))
                                std::cout << "[" << k << ":" << v << "]";
                            else
                                std::cout << "not found";
                            std::cout << "\n";
                        }
                    }
                    else
                    {
                        std::string k = cmd.substr(0, pos);
                        std::string v = cmd.substr(pos + 1);
                        d.add_or_update(k, v);
                    }					
                }
                break;
            }
        }
    }
}

int linear_probing_hashtable_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using linear_probing_hashtable::test_interactive;
    
    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}