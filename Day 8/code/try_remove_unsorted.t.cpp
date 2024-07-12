//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "try_remove_unsorted.hpp"
#include "helpers_and_types.hpp"

#include <cstddef>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>

namespace try_remove_unsorted
{
    namespace internal
    {
        template<typename Container>
        static void display(Container& xs, const char* label = nullptr)
        {
            static std::size_t n = 0;
            std::cout << std::setw(5) << (n++ / 2) << " ";
            if (label) std::cout << label << ":[ ";
            for (auto x : xs) std::cout << x << " ";
            std::cout << "]\n";
        }
    }

    static bool try_position_to_remove(std::vector<int>& xs)
    {
        std::size_t pos;
        std::cout << "position to remove: ";
        if (std::cin >> pos)
        {
            try_remove_unsorted(xs, pos);
            return true;
        }
        return false;
    }

    static bool try_item_to_remove(std::vector<int>& xs)
    {
        int x;
        std::cout << "item to remove: ";
        if (std::cin >> x)
        {
            try_remove_unsorted(xs, std::find(xs.begin(), xs.end(), x));
            return true;
        }
        return false;
    }

    static void test_interactive()
    {
        std::size_t n;
        std::cout << "collection suggested capacity: ";
        if (std::cin >> n)
        {
            if (n > 1)
            {
                seed_rand(now_since_epoch());
                std::size_t m = rand_int(static_cast<int>(n / 2), static_cast<int>(n) - 1);
                std::vector<int> ys = generate_random_ints(m, 1, 9);
                std::vector<int> xs;
                xs.reserve(n);
                std::cout << "collection capacity [before shrink]: " << xs.capacity() << "\n";
                std::copy(ys.begin(), ys.end(), std::back_inserter(xs));
                xs.shrink_to_fit();
                std::cout << "collection capacity [ after shrink]: " << xs.capacity() << "\n";
                while (true)
                {
                    std::cout << "collection size: " << xs.size() << "\n";
                    if (xs.empty()) 
                    {
                        std::cout << "\tnothing";
                        break;
                    }
                    else
                    {
                        internal::display(xs, "before remove");
                        if (try_item_to_remove(xs))
                        //if (try_position_to_remove(xs))
                            internal::display(xs, " after remove");
                        else
                            break;
                    }
                }
            }
            else
            {
                std::cout << "collection suggested capacity less than 2";
            }
        }
        std::cout << "\n";
    }
}

int try_remove_unsorted_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using try_remove_unsorted::test_interactive;
    
    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}