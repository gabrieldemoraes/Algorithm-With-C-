//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "sorting_quicksort.hpp"
#include "helpers_and_types.hpp"

#include "dynamic_array.hpp"
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>

#include "picobench.hpp"

namespace sorting_quicksort
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

    static std::vector<int> get_singleton_test_vector(std::size_t n)
    {
        static std::map<std::size_t, std::vector<int>> dic;
        auto iter = dic.find(n);
        if (iter == dic.end())
        {
            std::vector<int> xs = generate_random_ints(n, 1, 2 * static_cast<int>(n));
            dic.emplace(n, xs);
            return xs;
        }
        return iter->second;
    }

    static void bench_vec_std_sort(picobench::state& s)
    {
        std::vector<int> xs = get_singleton_test_vector(s.iterations());

        s.start_timer();
        std::sort(xs.begin(), xs.end());
        s.stop_timer();

        auto it = xs.begin();
        auto it2 = xs.begin(); std::advance(it2, xs.size() - 1);
        std::cout << std::setw(7) << s.iterations() << "     bench_vec_std_sort: "
            << std::setw(2) << *it << " " << std::setw(7) << *it2 << "\n";
    }

    static void bench_vec_quicksort(picobench::state& s)
    {
        std::vector<int> xs = get_singleton_test_vector(s.iterations());

        s.start_timer();
        quicksort(xs);
        s.stop_timer();

        auto it = xs.begin();
        auto it2 = xs.begin(); std::advance(it2, xs.size() - 1);
        std::cout << std::setw(7) << s.iterations() << "    bench_vec_quicksort: "
            << std::setw(2) << *it << " " << std::setw(7) << *it2 << "\n";
    }

    static void register_benchmarks()
    {
        std::vector<int> ITERS{ 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576 };
    
        picobench::global_registry::set_bench_suite("quicksort");
        picobench::global_registry::new_benchmark("bench_vec_std_sort", bench_vec_std_sort).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_vec_quicksort", bench_vec_quicksort).iterations(ITERS).baseline();
    }

    static void test_case_1()
    {
        {
            std::vector<int> xs{ 59, 1, 95, 40, 90, 90, 13, 95, 13, 71, 72, 86, 61, 51, 46, 12 };
            internal::display(xs, " before quicksort");
            //sorting_quicksort::quicksort(xs);
            sorting_quicksort::quicksort_shuffled(xs);
            internal::display(xs, "  after quicksort");
        }
        {
            std::vector<int> xs = generate_random_ints(16, 1, 100);
            internal::display(xs, " before quicksort");
            //sorting_quicksort::quicksort(xs);
            sorting_quicksort::quicksort_shuffled(xs);
            internal::display(xs, "  after quicksort");
        }
        {
            std::vector<int> xs = generate_random_ints(15, 1, 100);
            internal::display(xs, " before quicksort");
            //sorting_quicksort::quicksort(xs);
            sorting_quicksort::quicksort_shuffled(xs);
            internal::display(xs, "  after quicksort");
        }
        {
            std::vector<int> xs = generate_random_ints(9, 1, 3);
            internal::display(xs, " before quicksort");
            //sorting_quicksort::quicksort(xs);
            sorting_quicksort::quicksort_shuffled(xs);
            internal::display(xs, "  after quicksort");
        }
        {
            std::vector<int> xs = generate_random_ints(3, 1, 3);
            internal::display(xs, " before quicksort");
            //sorting_quicksort::quicksort(xs);
            sorting_quicksort::quicksort_shuffled(xs);
            internal::display(xs, "  after quicksort");
        }
        {
            std::vector<int> xs = generate_random_ints(rand_int(0, 4), 1, 4);
            internal::display(xs, " before quicksort");
            //sorting_quicksort::quicksort(xs);
            sorting_quicksort::quicksort_shuffled(xs);
            internal::display(xs, "  after quicksort");
        }
        {
            std::vector<int> ys = generate_random_ints(16, 1, 100);
            dynamic_array::dynamic_array<int> xs(ys.size());
            for (int y : ys) xs.add(y);
            internal::display(xs, " before quicksort");
            //sorting_quicksort::quicksort(xs);
            sorting_quicksort::quicksort_shuffled(xs);
            internal::display(xs, "  after quicksort");
        }
        {
            std::vector<int> ys = generate_random_ints(rand_int(0, 10), 1, 10);
            dynamic_array::dynamic_array<int> xs(ys.size());
            for (int y : ys) xs.add(y);
            internal::display(xs, " before quicksort");
            //sorting_quicksort::quicksort(xs);
            sorting_quicksort::quicksort_shuffled(xs);
            internal::display(xs, "  after quicksort");
        }
    }

    static void test_case_2()
    {
        {
            std::vector<int> xs{ 59, 1, 95, 40, 90, 90, 13, 95, 13, 71, 72, 86, 61, 51, 46, 12 };
            internal::display(xs, "  before median 3");
            std::size_t pos0 = 0, pos1 = xs.size() / 2, pos2 = xs.size() - 1;
            std::size_t pos = sorting_quicksort::internal::median_of_3(xs, pos0, pos1, pos2);
            std::vector<int> result{ xs[pos0], xs[pos1], xs[pos2], xs[pos] };
            internal::display(result, "   after median 3");
        }
        {
            std::vector<int> xs = generate_random_ints(16, 1, 100);
            internal::display(xs, "  before median 3");
            std::size_t pos0 = 0, pos1 = xs.size() / 2, pos2 = xs.size() - 1;
            std::size_t pos = sorting_quicksort::internal::median_of_3(xs, pos0, pos1, pos2);
            std::vector<int> result{ xs[pos0], xs[pos1], xs[pos2], xs[pos] };
            internal::display(result, "   after median 3");
        }
        {
            std::vector<int> xs = generate_random_ints(15, 1, 100);
            internal::display(xs, "  before median 3");
            std::size_t pos0 = 0, pos1 = xs.size() / 2, pos2 = xs.size() - 1;
            std::size_t pos = sorting_quicksort::internal::median_of_3(xs, pos0, pos1, pos2);
            std::vector<int> result{ xs[pos0], xs[pos1], xs[pos2], xs[pos] };
            internal::display(result, "   after median 3");
        }

        {
            std::vector<int> xs = generate_random_ints(9, 1, 3);
            internal::display(xs, "  before median 3");
            std::size_t pos0 = 0, pos1 = xs.size() / 2, pos2 = xs.size() - 1;
            std::size_t pos = sorting_quicksort::internal::median_of_3(xs, pos0, pos1, pos2);
            std::vector<int> result{ xs[pos0], xs[pos1], xs[pos2], xs[pos] };
            internal::display(result, "   after median 3");
        }
        {
            std::vector<int> xs = generate_random_ints(3, 1, 3);
            internal::display(xs, "  before median 3");
            std::size_t pos0 = 0, pos1 = xs.size() / 2, pos2 = xs.size() - 1;
            std::size_t pos = sorting_quicksort::internal::median_of_3(xs, pos0, pos1, pos2);
            std::vector<int> result{ xs[pos0], xs[pos1], xs[pos2], xs[pos] };
            internal::display(result, "   after median 3");
        }
        {
            std::vector<int> xs = generate_random_ints(rand_int(3, 4), 1, 4);
            internal::display(xs, "  before median 3");
            std::size_t pos0 = 0, pos1 = xs.size() / 2, pos2 = xs.size() - 1;
            std::size_t pos = sorting_quicksort::internal::median_of_3(xs, pos0, pos1, pos2);
            std::vector<int> result{ xs[pos0], xs[pos1], xs[pos2], xs[pos] };
            internal::display(result, "   after median 3");
        }
        {
            std::vector<int> ys = generate_random_ints(16, 1, 100);
            dynamic_array::dynamic_array<int> xs(ys.size());
            for (int y : ys) xs.add(y);
            ys = std::vector<int>(xs.begin(), xs.end());
            internal::display(ys, "  before median 3");
            std::size_t pos0 = 0, pos1 = xs.size() / 2, pos2 = xs.size() - 1;
            std::size_t pos = sorting_quicksort::internal::median_of_3(xs, pos0, pos1, pos2);
            std::vector<int> result{ xs[pos0], xs[pos1], xs[pos2], xs[pos] };
            internal::display(result, "   after median 3");
        }
        {
            std::vector<int> ys = generate_random_ints(rand_int(3, 10), 1, 10);
            dynamic_array::dynamic_array<int> xs(ys.size());
            for (int y : ys) xs.add(y);
            ys = std::vector<int>(xs.begin(), xs.end());
            internal::display(ys, "  before median 3");
            std::size_t pos0 = 0, pos1 = xs.size() / 2, pos2 = xs.size() - 1;
            std::size_t pos = sorting_quicksort::internal::median_of_3(xs, pos0, pos1, pos2);
            std::vector<int> result{ xs[pos0], xs[pos1], xs[pos2], xs[pos] };
            internal::display(result, "   after median 3");
        }
    }

    static void test_interactive()
    {
        std::cout << "1: sort a random vector of ints\n";
        std::cout << "2: sort a random vectors of people\n";
        std::cout << "3: run other samples, EOF: benchmark\n";

        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '1':
            {
                std::size_t n;
                std::cout << "collection size: "; std::cin >> n;
                std::vector<int> xs = generate_random_ints(n, 1, 3 * static_cast<int>(n));
                if (xs.empty())
                {
                    std::cout << "nothing";
                }
                else
                {
                    for (auto x : xs) std::cout << x << " ";
                    std::cout << "\n";
                }
                std::cout << "\n";
                if (!xs.empty())
                {
                    std::cout << "collection sorted:\n";
                    quicksort(xs);
                    for (auto x : xs) std::cout << x << " ";
                    std::cout << "\n";
                }
            }
            break;
            case '2':
            {
                std::size_t n;
                std::cout << "collection size: "; std::cin >> n;
                std::vector<std::string> boys = load_male_first_names_file();
                std::vector<std::string> girls = load_female_first_names_file();
                std::vector<std::string> surnames = load_surnames_file();
                std::vector<person> xs = generate_random_people(n, boys, girls, surnames);
                if (xs.empty())
                {
                    std::cout << "nothing";
                }
                else
                {
                    for (auto x : xs) std::cout << to_string(x) << " ";
                    std::cout << "\n";
                }
                std::cout << "\n";
                if (!xs.empty())
                {
                    std::cout << "collection sorted:\n";
                    quicksort(xs);
                    for (auto x : xs) std::cout << to_string(x) << "\n";
                    std::cout << "\n";
                }
            }
            break;
            case '3':
            {
                test_case_1();
                test_case_2();
            }
            break;
            default:
                std::cout << "input ignored\n";
                break;
            }
        }
    }
}

int sorting_quicksort_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using sorting_quicksort::test_interactive;
    using sorting_quicksort::register_benchmarks;

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