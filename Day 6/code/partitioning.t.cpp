//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "partitioning.hpp"
#include "helpers_and_types.hpp"

#include <cstddef>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

namespace partitioning
{
    namespace internal
    {
        template<typename T>
        static void display(const std::vector<T>&xs, std::size_t pivot_index, const char* label = nullptr)
        {
            if (label) std::cout << label << ": ";
            auto begin = xs.begin();
            auto pivot = begin + pivot_index;
            auto end = xs.end();
            for (auto it = begin; it != pivot; ++it) std::cout << *it << " ";
            std::cout << "[" << *pivot << "] ";
            for (auto it = pivot + 1; it != end; ++it) std::cout << *it << " ";
            std::cout << "\n";
        }

        template<typename Container>
        static void display(const Container&xs, typename Container::iterator pivot, const char* label = nullptr)
        {
            if (label) std::cout << label << ": ";
            for (auto it = xs.begin(); it != pivot; ++it) std::cout << *it << " ";
            std::cout << "[" << *pivot << "] ";
            for (auto it = std::next(pivot); it != xs.end(); ++it) std::cout << *it << " ";
            std::cout << "\n";
        }
    }

    static void test_case_1()
    {
        {
            for (std::size_t i : {0, 3, 5, 6, 9, 11})
            {
                {
                    std::vector<int> xs{ 10, 80, 22, 1, 5, 14, 88, 19, 71, 33, 26, 22 };
                    auto pivot = xs.begin() + i;
                    pivot = partitioning::partition(xs.begin(), xs.end(), pivot);
                    internal::display(xs, pivot, "        partition");
                }
                {
                    std::list<int> xs{ 10, 80, 22, 1, 5, 14, 88, 19, 71, 33, 26, 22 };
                    auto pivot = xs.begin(); std::advance(pivot, i);
                    pivot = partitioning::partition(xs.begin(), xs.end(), pivot);
                    internal::display(xs, pivot, "        partition");
                }
                {
                    std::vector<int> xs{ 10, 80, 22, 1, 5, 14, 88, 19, 71, 33, 26, 22 };
                    std::size_t pivot = partitioning::inplace_partition(xs, i);
                    internal::display(xs, pivot, "inplace_partition");
                }
            }
        }
        {
            for (std::size_t i : {0, 2, 6, 8, 9})
            {
                {
                    std::vector<int> xs{ 43, 43, 41, 5, 29, 6, 16, 19, 43, 8 };
                    auto pivot = xs.begin() + i;
                    pivot = partitioning::partition(xs.begin(), xs.end(), pivot);
                    internal::display(xs, pivot, "        partition");
                }
                {
                    std::list<int> xs{ 43, 43, 41, 5, 29, 6, 16, 19, 43, 8 };
                    auto pivot = xs.begin(); std::advance(pivot, i);
                    pivot = partitioning::partition(xs.begin(), xs.end(), pivot);
                    internal::display(xs, pivot, "        partition");
                }
                {
                    std::vector<int> xs{ 43, 43, 41, 5, 29, 6, 16, 19, 43, 8 };
                    std::size_t pivot = partitioning::inplace_partition(xs, i);
                    internal::display(xs, pivot, "inplace_partition");
                }
            }
        }
        {
            for (std::size_t i : {0, 7, 9, 12})
            {
                {
                    std::vector<int> xs{ 74, 48, 53, 26, 32, 45, 66, 66, 55, 25, 55, 25, 67, 8, 22 };
                    auto pivot = xs.begin() + i;
                    pivot = partitioning::partition(xs.begin(), xs.end(), pivot);
                    internal::display(xs, pivot, "        partition");
                }
                {
                    std::list<int> xs{ 74, 48, 53, 26, 32, 45, 66, 66, 55, 25, 55, 25, 67, 8, 22 };
                    auto pivot = xs.begin(); std::advance(pivot, i);
                    pivot = partitioning::partition(xs.begin(), xs.end(), pivot);
                    internal::display(xs, pivot, "        partition");
                }
                {
                    std::vector<int> xs{ 74, 48, 53, 26, 32, 45, 66, 66, 55, 25, 55, 25, 67, 8, 22 };
                    std::size_t pivot = partitioning::inplace_partition(xs, i);
                    internal::display(xs, pivot, "inplace_partition");
                }
            }
        }
        {
            for (std::size_t i : {0, 5})
            {
                {
                    std::vector<int> xs{ 41, 41, 41, 41, 41, 41 };
                    auto pivot = xs.begin() + i;
                    pivot = partitioning::partition(xs.begin(), xs.end(), pivot);
                    internal::display(xs, pivot, "        partition");
                }
                {
                    std::list<int> xs{ 41, 41, 41, 41, 41, 41 };
                    auto pivot = xs.begin(); std::advance(pivot, i);
                    pivot = partitioning::partition(xs.begin(), xs.end(), pivot);
                    internal::display(xs, pivot, "        partition");
                }
                {
                    std::vector<int> xs{ 41, 41, 41, 41, 41, 41 };
                    std::size_t pivot = partitioning::inplace_partition(xs, i);
                    internal::display(xs, pivot, "inplace_partition");
                }
            }
        }
        {
            for (std::size_t i : {0, 5, 9})
            {
                {
                    std::vector<int> xs{ 7, 35, 26, 24, 33, 18, 17, 13, 15, 7 };
                    auto pivot = xs.begin() + i;
                    pivot = partitioning::partition(xs.begin(), xs.end(), pivot);
                    internal::display(xs, pivot, "        partition");
                }
                {
                    std::list<int> xs{ 7, 35, 26, 24, 33, 18, 17, 13, 15, 7 };
                    auto pivot = xs.begin(); std::advance(pivot, i);
                    pivot = partitioning::partition(xs.begin(), xs.end(), pivot);
                    internal::display(xs, pivot, "        partition");
                }
                {
                    std::vector<int> xs{ 7, 35, 26, 24, 33, 18, 17, 13, 15, 7 };
                    std::size_t pivot = partitioning::inplace_partition(xs, i);
                    internal::display(xs, pivot, "inplace_partition");
                }
            }
        }
    }

    static void test_interactive()
    {
        std::cout << "1: partitioning a vector of ints\n";
        std::cout << "2: partitioning a list of ints\n";
        std::cout << "3: run other samples\n";

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '1':
            {
                std::size_t n, p;
                std::cout << "collection size: "; std::cin >> n;
                std::vector<int> xs = generate_random_ints(n, 1, 5 * static_cast<int>(n));
                for (int x : xs) std::cout << x << " ";
                std::cout << "\n";
                std::cout << "pivot: "; std::cin >> p;
                auto begin = xs.begin();
                auto end = xs.end();
                auto pivot = std::find(begin, end, p);
                if (pivot != end)
                {
                    p = inplace_partition(xs, std::distance(begin, pivot));
                    //p = std::distance(begin, partitioning::partition(begin, end, std::distance(begin, pivot)));
                    internal::display(xs, p);
                }
                else
                {
                    std::cout << "pivot not found\n";
                }
            }
            break;
            case '2':
            {
                std::size_t n, p;
                std::cout << "collection size: "; std::cin >> n;
                std::list<int> xs = to_list(generate_random_ints(n, 1, 5 * static_cast<int>(n)));
                for (int x : xs) std::cout << x << " ";
                std::cout << "\n";
                std::cout << "pivot: "; std::cin >> p;
                auto begin = xs.begin();
                auto end = xs.end();
                auto pivot = std::find(begin, end, p);
                if (pivot != end)
                {
                    pivot = partitioning::partition(begin, end, pivot);
                    internal::display(xs, pivot);
                }
                else
                {
                    std::cout << "pivot not found\n";
                }
            }
            break;
            case '3':
            {
                test_case_1();				
            }
            break;
            default:
                std::cout << "input ignored\n";
                break;
            }
        }
    }
}

int partitioning_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using partitioning::test_interactive;	

    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}