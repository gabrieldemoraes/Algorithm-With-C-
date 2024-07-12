//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 substring_searcher_samples.cpp -o substring_searcher_samples.exe
//cl /Fo.\obj\ /EHsc /O2 substring_searcher_samples.cpp /link /out:substring_searcher_samples.exe

#include "helpers_and_types.hpp"

#define PICOBENCH_IMPLEMENT
#include "picobench.hpp"

#include "substring_brute_force_searcher.hpp"
#include "substring_kmp_searcher.hpp"
#include "substring_rk_searcher.hpp"
#include "substring_bm_searcher.hpp"

#include <cstddef>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

template <typename SS>
void test_1(const SS& ss)
{
    std::string texts[]{ "FINDING A NEEDLE IN A HAYSTACK", "ABRACADABRA", "BBBABCABRA", "XXXXABRA", "XABCXABRA", "XXXXXABRABCABRA", "ABC" };
    std::cout << (int)ss.search(texts[1]) << ' ';
    std::cout << (ss.search(texts[0]) == std::string::npos ? "(NOT FOUND)" : "(FOUND)") << ' ';
    std::cout << (int)ss.search(texts[1], 2) << ' ';
    std::cout << (int)ss.search(texts[2]) << ' ';
    std::cout << (int)ss.search(texts[3]) << ' ';
    std::cout << (int)ss.search(texts[4]) << ' ';
    std::cout << (int)ss.search(texts[5], 6) << ' ';
    std::cout << (int)ss.search(texts[6]) << ' ';
    std::cout << '\n';
}

namespace benchmark
{
    int run_benchmark(int argc, char* argv[])
    {
        picobench::runner runner;
        runner.parse_cmd_line(argc, argv);
        return runner.run();
    }

    const std::string& get_singleton_test_string()
    {
        static std::string s = generate_random_string(1'000'000);
        return s;
    }

    const std::vector<std::string> get_dna_string_vec()
    {
        std::vector<dna> dna_data = load_human_dna_file();
        std::vector<std::string> temp; temp.reserve(dna_data.size());
        std::transform(dna_data.begin(), dna_data.end(), std::back_inserter(temp), [](dna& x) { return x.dna_sequence; });
        return temp;
    }

    const std::vector<std::string>& get_singleton_test_string_vec()
    {
        static std::vector<std::string> temp = get_dna_string_vec();
        return temp;
    }

    template <typename SUBSTRING_SEARCHER>
    void bench_string(picobench::state& s)
    {
        const std::string& text = get_singleton_test_string();
        //std::string pattern = text.substr(0, 3); pattern += '?'; //not found
        std::string pattern = text.substr(0, 30); pattern += '?'; //not found
        SUBSTRING_SEARCHER ss(pattern);
        int n = s.iterations(), counter = 0;
        s.start_timer();
        while(n--)
        {
            if (std::string::npos != ss.search(text))
                ++counter;
        }
        s.stop_timer();
        std::cout << s.iterations() << ' ' << pattern.substr(0, 15) << ' ' << counter << '\n';
    }

    template <typename SUBSTRING_SEARCHER>
    void bench_dna(picobench::state& s)
    {
        const std::vector<std::string>& data = get_singleton_test_string_vec();
        std::string pattern = "ACTGACAACAT"; //not found 
        //std::string pattern = "ACTGACAACA"; //found some
        //std::string pattern = "ACTGACAACAGCAACCTGTGTTA"; //found few
        SUBSTRING_SEARCHER ss(pattern);
        int n = std::min<int>(s.iterations(), data.size()), m = (n >> 4), counter = 0;
        s.start_timer();
        while(m--)
        {
            for (int i = 0; i < n; ++i)
            {
                const std::string& text = data[i];
                if (std::string::npos != ss.search(text))
                    ++counter;
            }
        }
        s.stop_timer();
        std::cout << n << ' ' << pattern.substr(0, 15) << ' ' << counter << '\n';
    }
    
    void register_benchmarks()
    {
        std::vector<int> ITERS { 1 << 5, 1 << 6, 1 << 7, 1 << 8, 1 << 9, 1 << 10 };

        picobench::global_registry::set_bench_suite("substring_search string pattern");
        picobench::global_registry::new_benchmark("bench_brute_force_str", bench_string<substring_searcher::brute_force>).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_kmp_str", bench_string<substring_searcher::knuth_morris_pratt>).iterations(ITERS);
        //picobench::global_registry::new_benchmark("bench_rk_str", bench_string<substring_searcher::rabin_karp>).iterations(ITERS);
        //picobench::global_registry::new_benchmark("bench_bm_str", bench_string<substring_searcher::boyer_moore>).iterations(ITERS);
        
        std::vector<int> ITERS2 { 1 << 5, 1 << 6, 1 << 7, 1 << 8, 1 << 9, 1 << 10, 1 << 11, 1 << 12 };

        picobench::global_registry::set_bench_suite("substring_search dna pattern");
        picobench::global_registry::new_benchmark("bench_brute_force_dna", bench_dna<substring_searcher::brute_force>).iterations(ITERS2);
        picobench::global_registry::new_benchmark("bench_kmp_dna", bench_dna<substring_searcher::knuth_morris_pratt>).iterations(ITERS2);
        //picobench::global_registry::new_benchmark("bench_rk_dna", bench_dna<substring_searcher::rabin_karp>).iterations(ITERS2);
        //picobench::global_registry::new_benchmark("bench_bm_dna", bench_dna<substring_searcher::boyer_moore>).iterations(ITERS2);        
    }
}

int main(int argc, char* argv[])
{
    std::string patterns[] { "NEEDLE", "ABRA", "ABC" };
    for (int i = 0; i < 3; ++i)
    {
        //test_1(substring_searcher::boyer_moore(patterns[i]));
        //test_1(substring_searcher::rabin_karp(patterns[i]));
        test_1(substring_searcher::knuth_morris_pratt(patterns[i]));
        test_1(substring_searcher::brute_force(patterns[i]));

        std::cout << '\n';
    }

    benchmark::get_singleton_test_string();
    benchmark::get_singleton_test_string_vec();
    benchmark::register_benchmarks();
    return benchmark::run_benchmark(argc, argv);
}