//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "helpers_and_types.hpp"

#include <cstddef>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "sorting_mergesort.hpp"

#include "picobench.hpp"

namespace benchmarking_algorithms
{
    static std::vector<int> get_singleton_test_vector(std::size_t n)
    {
        static std::map<std::size_t, std::vector<int>> dic;
        auto iter = dic.find(n);
        if (iter == dic.end())
        {
            std::vector<int> xs = generate_random_ints(n, 1, 9);
            dic.emplace(n, xs);
            return xs;
        }
        return iter->second;
    }

    static std::vector<int> get_singleton_test_vector_ordered(std::size_t n)
    {
        static std::map<std::size_t, std::vector<int>> dic;
        auto iter = dic.find(n);
        if (iter == dic.end())
        {
            std::vector<int> xs = generate_ordered_random_ints(n, 1, static_cast<int>(10 * n));
            dic.emplace(n, xs);
            return xs;
        }
        return iter->second;
    }

    static std::size_t count_occurrences(const std::vector<int>& xs, int val)
    {
        return std::count(xs.begin(), xs.end(), val);
    }

    static void bench_count(picobench::state& s)
    {
        static int val = rand_int(1, 9);
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector(n);
        std::vector<std::size_t> counter;
        const int N = 128;
        counter.reserve(N);
        s.start_timer();
        for (int i = 0; i < N; ++i)
            counter.push_back(count_occurrences(xs, val));
        s.stop_timer();
        std::cout << std::setw(8) << n << ": " << std::setw(6) << counter[0] << " occurrences of " << val << "\n";
    }

    static int find_min(const std::vector<int>& xs)
    {
        return *std::min_element(xs.begin(), xs.end());
    }

    static void bench_min(picobench::state& s)
    {
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector(n);
        std::vector<std::size_t> min_val;
        const int N = 128;
        min_val.reserve(N);
        s.start_timer();
        for (int i = 0; i < N; ++i)
            min_val.push_back(find_min(xs));
        s.stop_timer();
        std::cout << std::setw(8) << n << ": " << min_val[0] << " is min\n";
    }

    static int find_max(const std::vector<int>& xs)
    {
        return *std::max_element(xs.begin(), xs.end());
    }

    static void bench_max(picobench::state& s)
    {
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector(n);
        std::vector<std::size_t> max_val;
        const int N = 128;
        max_val.reserve(N);
        s.start_timer();
        for (int i = 0; i < N; ++i)
            max_val.push_back(find_max(xs));
        s.stop_timer();
        std::cout << std::setw(8) << n << ": " << max_val[0] << " is max\n";
    }

    static void find_minmax(const std::vector<int>& xs, int& _min, int& _max)
    {
        auto result = std::minmax_element(xs.begin(), xs.end());
        _min = *result.first;
        _max = *result.second;
    }

    static void bench_minmax(picobench::state& s)
    {
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector(n);
        std::vector<std::size_t> min_val, max_val;
        const int N = 128;
        min_val.reserve(N);
        max_val.reserve(N);
        s.start_timer();
        for (int i = 0; i < N; ++i)
        {
            int _min_val, _max_val;
            find_minmax(xs, _min_val, _max_val);
            min_val.push_back(_min_val);
            max_val.push_back(_max_val);
        }
        s.stop_timer();
        std::cout << std::setw(8) << n << ": " << min_val[0] << " is min and " << max_val[0] << " is max\n";
    }

    static bool find_with_binary_search(const std::vector<int>& xs, int val)
    {
        return std::binary_search(xs.begin(), xs.end(), val);
    }

    static void bench_find_binsrch(picobench::state& s)
    {
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector_ordered(n);
        std::vector<bool> found;
        const int N = 256 * 1024;
        found.reserve(N);
        int val = n * 11;
        s.start_timer();
        for (int i = 0; i < N; ++i)
            found.push_back(find_with_binary_search(xs, val));
        s.stop_timer();
        std::cout << std::setw(8) << n << ": " << val << " found? " << std::boolalpha << found[0] << "\n";
    }

    static void sort_vector(std::vector<int>& xs)
    {
        std::sort(xs.begin(), xs.end());
    }

    static void bench_sort_vector(picobench::state& s)
    {
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector(n);
        std::vector<int> ys = xs;
        std::vector<std::size_t> first_item, last_item;
        const int N = 16;
        s.start_timer();
        for (int i = 0; i < N; ++i)
        {
            sort_vector(xs);
            first_item.push_back(xs[0]);
            last_item.push_back(xs[xs.size() - 1]);
            xs = ys;
        }			
        s.stop_timer();
        std::cout << std::setw(8) << n << ": " << first_item[0] << " is the first item and " << last_item[0] << " is the last item\n";
    }

    static void mergesort_vector(std::vector<int>& xs)
    {
        sorting_mergesort::mergesort(xs);
    }

    static void bench_mergesort_vector(picobench::state& s)
    {
        int n = s.iterations();
        std::vector<int> xs = get_singleton_test_vector(n);
        std::vector<int> ys = xs;
        std::vector<std::size_t> first_item, last_item;
        const int N = 16;
        s.start_timer();
        for (int i = 0; i < N; ++i)
        {
            mergesort_vector(xs);
            first_item.push_back(xs[0]);
            last_item.push_back(xs[xs.size() - 1]);
            xs = ys;
        }			
        s.stop_timer();
        std::cout << std::setw(8) << n << ": " << first_item[0] << " is the first item and " << last_item[0] << " is the last item\n";
    }

    static void bench_quadradic_count(picobench::state& s)
    {
        int counter = 0;
        int n = s.iterations();
        s.start_timer();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                counter += rand_int();
        s.stop_timer();
        std::cout << std::setw(8) << n << ": " << counter << " (quadradic)\n";
    }

    static void bench_cubic_count(picobench::state& s)
    {
        int counter = 0;
        int n = s.iterations();
        s.start_timer();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    counter += rand_int();
        s.stop_timer();
        std::cout << std::setw(8) << n << ": " << counter << " (cubic)\n";
    }

    static void register_benchmarks()
    {
        std::vector<int> ITERS{ 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576 };
        
        picobench::global_registry::set_bench_suite("counting occurrences of a value");
        picobench::global_registry::new_benchmark("bench_count", bench_count).iterations(ITERS);

        picobench::global_registry::set_bench_suite("finding minimum");
        picobench::global_registry::new_benchmark("bench_min", bench_min).iterations(ITERS);

        picobench::global_registry::set_bench_suite("finding maximum");
        picobench::global_registry::new_benchmark("bench_max", bench_max).iterations(ITERS);

        picobench::global_registry::set_bench_suite("finding minimum and maximum");
        picobench::global_registry::new_benchmark("bench_minmax", bench_minmax).iterations(ITERS);

        picobench::global_registry::set_bench_suite("finding value with binary search");
        picobench::global_registry::new_benchmark("bench_find_binsrch", bench_find_binsrch).iterations(ITERS);

        picobench::global_registry::set_bench_suite("sorting vector with introsort (std::sort)");
        picobench::global_registry::new_benchmark("bench_sort_vector", bench_sort_vector).iterations(ITERS);

        picobench::global_registry::set_bench_suite("sorting vector with mergesort (std::stable_sort)");
        picobench::global_registry::new_benchmark("bench_mergesort_vector", bench_mergesort_vector).iterations(ITERS);

        std::vector<int> ITERS2{ 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7, 1 << 8, 1 << 9, 1 << 10 };
        
        picobench::global_registry::set_bench_suite("quadratic random counting");
        picobench::global_registry::new_benchmark("bench_quadradic_count", bench_quadradic_count).iterations(ITERS2);

        picobench::global_registry::set_bench_suite("cubic random counting");
        picobench::global_registry::new_benchmark("bench_cubic_count", bench_cubic_count).iterations(ITERS2);
    }
}

int benchmarking_algorithms_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using benchmarking_algorithms::register_benchmarks;

    if (reg_benchmarks)
    {
        register_benchmarks();
    }

    return 0;
}