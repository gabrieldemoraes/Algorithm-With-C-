//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "helpers_and_types.hpp"

#include <vector>
#include <set>
#include <string>
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <chrono>

namespace blocklist
{
    static inline bool brute_force_check(const std::vector<std::string>& blocklist, const std::string& target)
    {
        return std::find(blocklist.begin(), blocklist.end(), target) != blocklist.end();
    }

    static inline bool binary_search_check(const std::vector<std::string>& blocklist, const std::string& target)
    {
        //assert(std::is_sorted(blocklist.begin(), blocklist.end()));
        return std::binary_search(blocklist.begin(), blocklist.end(), target);
    }

    class brute_force_blocklist_checker
    {
        std::vector<std::string>& blocklist;
    public:	
        brute_force_blocklist_checker(std::vector<std::string>& blocklist) 
            : blocklist(blocklist) {}

        bool check(const std::string& target) const
        {
            return brute_force_check(blocklist, target);
        }

        const char* solution() const
        {
            return "brute force";
        }
    };

    class binary_search_blocklist_checker
    {
        std::vector<std::string>& blocklist;
    public:
        binary_search_blocklist_checker(std::vector<std::string>& blocklist)
            : blocklist(blocklist) 
        {
            std::sort(blocklist.begin(), blocklist.end());
        }

        bool check(const std::string& target) const
        {
            return binary_search_check(blocklist, target);
        }

        const char* solution() const
        {
            return "sort then binary search";
        }
    };

    class set_blocklist_checker
    {
        std::set<std::string> blocklist;
        std::set<std::string>::iterator blocklist_end;
    public:
        set_blocklist_checker(std::vector<std::string>& blocklist)
            : blocklist(blocklist.begin(), blocklist.end())
        {
            blocklist.clear();
            blocklist_end = this->blocklist.end();
        }

        bool check(const std::string& target) const
        {
            return blocklist.find(target) != blocklist_end;
        }

        const char* solution() const
        {
            return "set";
        }
    };

    template <typename CheckPolicy>
    class blocklist_checker final : private CheckPolicy
    {
        using CheckPolicy::check;
        using CheckPolicy::solution;
    public:
        blocklist_checker(std::vector<std::string>& blocklist) : CheckPolicy(blocklist) {}

        bool operator()(const std::string& target) const
        {
            return check(target);
        }

        const char* solution() const
        {
            return CheckPolicy::solution();
        }
    };

    static int run_solution(const char* FILENAME)
    {
        //PROBLEM: Build a blocklist of strings
        
        //INPUT: FILENAME
        //FILENAME is the blocklist
        //The following inputs are checked against the entries in the blocklist
        //If exists then echo it to the standard output

        std::vector<std::string> blocklist = std::move(load_file(FILENAME));
        std::size_t N = blocklist.size();
        
        if (N > 0)
        {
            auto start = std::chrono::high_resolution_clock::now();
                        
            //SOLUTION:
            //blocklist_checker<brute_force_blocklist_checker> bc(blocklist);
            //blocklist_checker<binary_search_blocklist_checker> bc(blocklist);
            blocklist_checker<set_blocklist_checker> bc(blocklist);

            //OUTPUT: List of input denied
            std::size_t count = 0; std::string target;
            while (std::cin >> target)
            {
                if (bc(target))
                {
                    ++count;
                    std::cout << target << std::endl;
                }
            }

            auto stop = std::chrono::high_resolution_clock::now();
            std::cerr << "Solution = " << bc.solution() << "\n";
            std::cerr << "Denied = " << count << "\n";
            //std::cerr << "Time elapsed = " << ((stop - start).count()) << " nanoseconds\n";
            //std::cerr << "Time elapsed = " << ((stop - start).count() / 1000.0) << " microseconds\n";
            std::cerr << "Time elapsed = " << ((stop - start).count() / 1000000.0) << " milliseconds\n";
        }

        return 0;
    }
}

//Test cases:
//blocklist.exe blocklist1.txt < blocklist-targets1.txt > nul
//blocklist.exe blocklist2.txt < blocklist-targets2.txt > nul
//blocklist.exe blocklist3.txt < blocklist-targets3.txt > nul
//blocklist.exe blocklist4.txt < blocklist-targets4.txt > nul
int blocklist_main(int argc, char *argv[], bool run)
{
    using blocklist::run_solution;

    if (run && argc > 1)
    {
        return run_solution(argv[1]);
    }

    return 0;
}