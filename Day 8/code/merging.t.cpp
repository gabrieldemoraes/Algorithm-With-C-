//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "merging.hpp"
#include "helpers_and_types.hpp"

#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <map>

#include "picobench.hpp"

namespace merging
{
    namespace internal
    {
        template<typename Container>
        static void display(const Container& xs, const char* label = nullptr)
        {
            static std::size_t n = 0;
            std::cout << std::setw(5) << (n++ / 2) << " ";
            if (label) std::cout << label << ":[ ";
            for (auto x : xs) std::cout << x << " ";
            std::cout << "]\n";
        }
    }

    struct wrapped_int
    {
        bool side; //false (left), true (right)
        int val;
        operator int() const { return val; }
    };

    std::ostream& operator<<(std::ostream& os, wrapped_int i)
    {
        os << i.val << "(" << (i.side ? '2' : '1') << ")";
        return os;
    }

    static std::vector<int> get_singleton_test_vector(std::size_t n)
    {
        static std::map<std::size_t, std::vector<int>> dic;
        auto iter = dic.find(n);
        if (iter == dic.end())
        {
            std::vector<int> xs = generate_ordered_random_ints(n, 1, 2 * static_cast<int>(n));
            dic.emplace(n, xs);
            return xs;
        }
        return iter->second;
    }

    static void bench_vec_merge_copy(picobench::state& s)
    {
        std::vector<int> xs = get_singleton_test_vector(s.iterations());
        std::vector<int> ys = get_singleton_test_vector(s.iterations() + 1);
        std::vector<int> zs;
        
        s.start_timer();
        zs = merge_copy(xs, ys);
        s.stop_timer();
    }
    
    static void bench_vec_std_merge(picobench::state& s)
    {
        std::vector<int> xs = get_singleton_test_vector(s.iterations());
        std::vector<int> ys = get_singleton_test_vector(s.iterations() + 1);
        std::vector<int> zs;
        zs.reserve(xs.size() + ys.size());
        
        s.start_timer();
        std::merge(xs.begin(), xs.end(), ys.begin(), ys.end(), std::back_inserter(zs));
        s.stop_timer();
    }

    static void bench_vec_std_inp_merge(picobench::state& s)
    {
        std::vector<int> xs = get_singleton_test_vector(s.iterations());
        std::size_t mid = xs.size() / 2;
        
        s.start_timer();
        std::inplace_merge(xs.begin(), xs.begin() + mid, xs.end());
        s.stop_timer();

        auto it = xs.begin();
        auto it2 = xs.begin(); std::advance(it2, xs.size() - 1);
        std::cout << std::setw(7) << s.iterations() << " bench_vec_std_inp_merge: "
            << std::setw(2) << *it << " " << std::setw(7) << *it2 << "\n";
    }

    static void bench_vec_inp_merge(picobench::state& s)
    {
        std::vector<int> xs = get_singleton_test_vector(s.iterations());
        
        s.start_timer();
        inplace_merge(xs);
        s.stop_timer();
        
        auto it = xs.begin();
        auto it2 = xs.begin(); std::advance(it2, xs.size() - 1);
        std::cout << std::setw(7) << s.iterations() << "     bench_vec_inp_merge: "
            << std::setw(2) << *it << " " << std::setw(7) << *it2 << "\n";
    }

    static void bench_lst_std_inp_merge(picobench::state& s)
    {
        std::list<int> xs = to_list(get_singleton_test_vector(s.iterations()));
        std::size_t mid = std::distance(xs.begin(), xs.end()) / 2;
        
        s.start_timer();
        auto mid_it = xs.begin(); std::advance(mid_it, mid);
        std::inplace_merge(xs.begin(), mid_it, xs.end());
        s.stop_timer();

        auto it = xs.begin();
        auto it2 = xs.begin(); std::advance(it2, xs.size() - 1);
        std::cout << std::setw(7) << s.iterations() << " bench_lst_std_inp_merge: "
            << std::setw(2) << *it << " " << std::setw(7) << *it2 << "\n";
    }

    static void register_benchmarks()
    {
        std::vector<int> ITERS{ 32768, 65536, 131072, 262144, 524288, 1048576 };

        picobench::global_registry::set_bench_suite("merge");
        picobench::global_registry::new_benchmark("bench_vec_merge_copy", bench_vec_merge_copy).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_vec_std_merge", bench_vec_std_merge).iterations(ITERS);

        picobench::global_registry::set_bench_suite("inplace_merge");
        picobench::global_registry::new_benchmark("bench_vec_std_inp_merge", bench_vec_std_inp_merge).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_lst_std_inp_merge", bench_lst_std_inp_merge).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_vec_inp_merge", bench_vec_inp_merge).iterations(ITERS).baseline();
    }

    static void test_case_1()
    {
        {
            std::vector<int> xs{ 3, 4, 1, 2 };
            internal::display(xs, " before merge");
            inplace_merge(xs, 0, xs.size());
            internal::display(xs, "  after merge");
        }
        {
            std::vector<int> xs{ 3, 4, 1, 2, 5 };
            internal::display(xs, " before merge");
            inplace_merge(xs, 0, xs.size());
            internal::display(xs, "  after merge");
        }
        {
            std::vector<int> xs{ 3, 4, 1, 2 };
            internal::display(xs, " before merge");
            inplace_merge(xs, 0, xs.size());
            internal::display(xs, "  after merge");
        }
        {
            std::vector<int> xs{ 2, 1, 3 };
            internal::display(xs, " before merge");
            inplace_merge(xs, 0, xs.size());
            internal::display(xs, "  after merge");
        }
        {
            std::vector<int> xs{ 2, 1 };
            internal::display(xs, " before merge");
            inplace_merge(xs, 0, xs.size());
            internal::display(xs, "  after merge");
        }
        {
            std::vector<int> xs{ 2 };
            internal::display(xs, " before merge");
            inplace_merge(xs, 0, xs.size());
            internal::display(xs, "  after merge");
        }
        {
            std::vector<int> xs{ 6, 8, 2, 2, 6 };
            internal::display(xs, " before merge");
            inplace_merge(xs, 0, xs.size());
            internal::display(xs, "  after merge");
        }
    }

    static void test_case_2()
    {
        {
            std::vector<int> xs{ 3, 4, 1, 2 };
            internal::display(xs, " before merge");
            std::size_t mid = xs.size() / 2;
            std::inplace_merge(xs.begin(), xs.begin() + mid, xs.end());
            inplace_merge(xs, 0, xs.size());
            internal::display(xs, "  after merge");
        }
        {
            std::vector<int> xs{ 3, 4, 1, 2, 5 };
            internal::display(xs, " before merge");
            std::size_t mid = xs.size() / 2;
            std::inplace_merge(xs.begin(), xs.begin() + mid, xs.end());
            internal::display(xs, "  after merge");
        }
        {
            std::vector<int> xs{ 3, 4, 1, 2 };
            internal::display(xs, " before merge");
            std::size_t mid = xs.size() / 2;
            std::inplace_merge(xs.begin(), xs.begin() + mid, xs.end());
            internal::display(xs, "  after merge");
        }
        {
            std::vector<int> xs{ 2, 1, 3 };
            internal::display(xs, " before merge");
            std::size_t mid = xs.size() / 2;
            std::inplace_merge(xs.begin(), xs.begin() + mid, xs.end());
            internal::display(xs, "  after merge");
        }
        {
            std::vector<int> xs{ 2, 1 };
            internal::display(xs, " before merge");
            std::size_t mid = xs.size() / 2;
            std::inplace_merge(xs.begin(), xs.begin() + mid, xs.end());
            internal::display(xs, "  after merge");
        }
        {
            std::vector<int> xs{ 2 };
            internal::display(xs, " before merge");
            std::size_t mid = xs.size() / 2;
            std::inplace_merge(xs.begin(), xs.begin() + mid, xs.end());
            internal::display(xs, "  after merge");
        }
        {
            std::vector<int> xs{ 6, 8, 2, 2, 6 };
            internal::display(xs, " before merge");
            std::size_t mid = xs.size() / 2;
            std::inplace_merge(xs.begin(), xs.begin() + mid, xs.end());
            internal::display(xs, "  after merge");
        }
    }

    static void test_interactive()
    {
        std::cout << "1: merge two random vectors of ints\n";
        std::cout << "2: merge two random vectors of people\n";
        std::cout << "3: merge one random vector of ints (half/half sorted)\n";
        std::cout << "4: run other samples, EOF: benchmark\n";
        
        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '1':
                {
                    std::size_t n, m;
                    std::cout << "collection 1 size: "; std::cin >> n;
                    std::cout << "collection 2 size: "; std::cin >> m;
                    std::vector<int> xs = generate_ordered_random_ints(n, 1, 2 * static_cast<int>(n));
                    std::vector<int> ys = generate_ordered_random_ints(m, 1, 2 * static_cast<int>(m));
                    /*
                    std::vector<int> _xs = generate_ordered_random_ints(n, 1, 2 * static_cast<int>(n));
                    std::vector<int> _ys = generate_ordered_random_ints(m, 1, 2 * static_cast<int>(m));
                    std::vector<wrapped_int> xs, ys;
                    std::transform(_xs.begin(), _xs.end(), std::back_inserter(xs), [](int x) { return wrapped_int{ false, x }; });
                    std::transform(_ys.begin(), _ys.end(), std::back_inserter(ys), [](int y) { return wrapped_int{ true, y }; });
                    */
                    std::cout << "collection 1:\n"; 
                    if (xs.empty()) std::cout << "nothing"; 
                    else for (int x : xs) std::cout << x << " ";
                    std::cout << "\n";
                    std::cout << "collection 2:\n"; 
                    if (ys.empty()) std::cout << "nothing";
                    else for (int y : ys) std::cout << y << " ";
                    std::cout << "\n";
                    std::cout << "collections merged:\n";
                    std::vector<int> zs = merge_copy(xs, ys);
                    //std::vector<wrapped_int> zs = merge_copy(xs, ys);
                    if (zs.empty()) std::cout << "nothing";
                    else for (auto z : zs) std::cout << z << " ";
                    std::cout << "\n";
                }
                break;
            case '2':
                {
                    std::size_t n, m;
                    std::cout << "collection 1 size: "; std::cin >> n;
                    std::cout << "collection 2 size: "; std::cin >> m;					
                    std::vector<std::string> boys = load_male_first_names_file();
                    std::vector<std::string> girls = load_female_first_names_file();
                    std::vector<std::string> surnames = load_surnames_file();
                    std::vector<person> xs = generate_ordered_random_people(n, boys, girls, surnames);
                    std::vector<person> ys = generate_ordered_random_people(m, boys, girls, surnames);
                    std::cout << "collection 1:\n";
                    if (xs.empty()) std::cout << "nothing";
                    else for (auto& x : xs) std::cout << "[" << to_string(x) << "] ";
                    std::cout << "\n";
                    std::cout << "collection 2:\n"; 
                    if (ys.empty()) std::cout << "nothing";
                    else for (auto& y : ys) std::cout << "[" << to_string(y) << "] ";
                    std::cout << "\n";
                    std::cout << "collections merged:\n";
                    std::vector<person> zs = merge_copy(xs, ys);
                    if (zs.empty()) std::cout << "nothing";
                    else for (auto& z : zs) std::cout << "[" << to_string(z) << "] ";
                    std::cout << "\n";
                }
                break;
            case '3':
                {
                    std::size_t n;
                    std::cout << "collection size: "; std::cin >> n;
                    std::vector<int> xs = generate_random_ints(n, 1, 3 * static_cast<int>(n));
                    std::size_t mid = xs.size() / 2;
                    std::sort(xs.begin(), xs.begin() + mid);
                    std::sort(xs.begin() + mid, xs.end());
                    if (xs.empty())
                    {
                        std::cout << "nothing";
                    }
                    else
                    {
                        for (auto it = xs.begin(), end = xs.begin() + mid; it != end; ++it)
                            std::cout << *it << " ";
                        std::cout << "| ";
                        for (auto it = xs.begin() + mid, end = xs.end(); it != end; ++it)
                            std::cout << *it << " ";
                    }
                    std::cout << "\n";
                    if (!xs.empty())
                    {
                        std::cout << "collection merged inplace:\n";
                        inplace_merge(xs);
                        for (auto x : xs) std::cout << x << " ";
                        std::cout << "\n";
                    }
                }
                break;
                case '4':
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

int merging_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using merging::test_interactive;
    using merging::register_benchmarks;

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