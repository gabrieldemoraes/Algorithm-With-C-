//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "sorting_mergesort.hpp"
#include "helpers_and_types.hpp"

#include "dynamic_array.hpp"
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <map>

#include "picobench.hpp"

namespace sorting_mergesort
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

    static void bench_vec_std_stb_sort(picobench::state& s)
    {
        std::vector<int> xs = get_singleton_test_vector(s.iterations());
        
        s.start_timer();
        std::stable_sort(xs.begin(), xs.end());
        s.stop_timer();

        auto it = xs.begin();
        auto it2 = xs.begin(); std::advance(it2, xs.size() - 1);
        std::cout << std::setw(7) << s.iterations() << " bench_vec_std_stb_sort: "
            << std::setw(2) << *it << " " << std::setw(7) << *it2 << "\n";
    }

    static void bench_vec_mergesort(picobench::state& s)
    {
        std::vector<int> xs = get_singleton_test_vector(s.iterations());

        s.start_timer();
        mergesort(xs);
        s.stop_timer();

        auto it = xs.begin();
        auto it2 = xs.begin(); std::advance(it2, xs.size() - 1);
        std::cout << std::setw(7) << s.iterations() << "    bench_vec_mergesort: "
            << std::setw(2) << *it << " " << std::setw(7) << *it2 << "\n";
    }

    static void bench_lst_std_stb_sort(picobench::state& s)
    {
        std::list<int> xs = to_list(get_singleton_test_vector(s.iterations()));
        
        s.start_timer();
        //std::stable_sort(xs.begin(), xs.end()); //visual c++ has (non-standard) implementation!
        xs.sort();
        s.stop_timer();

        auto it = xs.begin();
        auto it2 = xs.begin(); std::advance(it2, xs.size() - 1);
        std::cout << std::setw(7) << s.iterations() << " bench_lst_std_stb_sort: "
            << std::setw(2) << *it << " " << std::setw(7) << *it2 << "\n";
    }

    static void register_benchmarks()
    {
        std::vector<int> ITERS{ 32768, 65536, 131072, 262144, 524288, 1048576 };
        
        picobench::global_registry::set_bench_suite("mergesort");
        picobench::global_registry::new_benchmark("bench_vec_std_stb_sort", bench_vec_std_stb_sort).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_lst_std_stb_sort", bench_lst_std_stb_sort).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_vec_mergesort", bench_vec_mergesort).iterations(ITERS).baseline();
    }

    static void test_case_1()	
    {
        {
            std::vector<int> xs{ 59, 1, 95, 40, 90, 90, 13, 95, 13, 71, 72, 86, 61, 51, 46, 12 };
            internal::display(xs, " before mergesort");
            sorting_mergesort::mergesort(xs);
            internal::display(xs, "  after mergesort");
        }
        {
            std::vector<int> xs = generate_random_ints(16, 1, 100);			
            internal::display(xs, " before mergesort");
            sorting_mergesort::mergesort(xs);
            internal::display(xs, "  after mergesort");
        }
        {
            std::vector<int> xs = generate_random_ints(15, 1, 100);
            internal::display(xs, " before mergesort");
            sorting_mergesort::mergesort(xs);
            internal::display(xs, "  after mergesort");
        }
        {
            std::vector<int> xs = generate_random_ints(9, 1, 3);
            internal::display(xs, " before mergesort");
            sorting_mergesort::mergesort(xs);
            internal::display(xs, "  after mergesort");
        }
        {
            std::vector<int> xs = generate_random_ints(3, 1, 3);
            internal::display(xs, " before mergesort");
            sorting_mergesort::mergesort(xs);
            internal::display(xs, "  after mergesort");
        }
        {
            std::vector<int> xs = generate_random_ints(rand_int(0, 4), 1, 4);
            internal::display(xs, " before mergesort");
            sorting_mergesort::mergesort(xs);
            internal::display(xs, "  after mergesort");
        }
        {
            std::vector<int> ys = generate_random_ints(16, 1, 100);
            dynamic_array::dynamic_array<int> xs(ys.size());
            for (int y : ys) xs.add(y);
            internal::display(xs, " before mergesort");
            sorting_mergesort::mergesort(xs);
            internal::display(xs, "  after mergesort");
        }
        {
            std::vector<int> ys = generate_random_ints(rand_int(0, 10), 1, 10);
            dynamic_array::dynamic_array<int> xs(ys.size());
            for (int y : ys) xs.add(y);
            internal::display(xs, " before mergesort");
            sorting_mergesort::mergesort(xs);
            internal::display(xs, "  after mergesort");
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
                    mergesort(xs);
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
                seed_rand(0);
                std::vector<person> xs = generate_random_people(n, boys, girls, surnames);
                if (xs.empty())
                {
                    std::cout << "nothing";
                }
                else
                {
                    //create some other people
                    xs.emplace_back(xs[0].gender, xs[0].first_name, xs[0].last_name, 18);
                    xs.emplace_back(xs[1].gender, xs[1].first_name, xs[0].last_name, 18);
                    xs.emplace_back(xs[0].gender, xs[0].first_name, xs[1].last_name, 18);
                    xs.emplace_back(xs[2].gender, xs[2].first_name, xs[0].last_name, 18);
                    xs.emplace_back(xs[3].gender, xs[3].first_name, xs[0].last_name, 18);

                    for (auto x : xs) std::cout << to_string(x) << " ";
                    std::cout << "\n";
                }
                std::cout << "\n";
                if (!xs.empty())
                {
                    std::cout << "collection sorted:\n";
                    mergesort(xs);
                    //std::stable_sort(xs.begin(), xs.end());
                    for (auto x : xs) std::cout << to_string(x) << "\n";
                    std::cout << "\n";
                    std::cout << "then sorted by decreasing age (sort stability):\n";
                    auto by_age = [](const person& lhs, const person& rhs) {
                        return lhs.age > rhs.age;
                    };
                    std::stable_sort(xs.begin(), xs.end(), by_age);
                    for (auto x : xs) std::cout << to_string(x) << "\n";
                    std::cout << "\n";
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

int sorting_mergesort_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using sorting_mergesort::test_interactive;
    using sorting_mergesort::register_benchmarks;

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