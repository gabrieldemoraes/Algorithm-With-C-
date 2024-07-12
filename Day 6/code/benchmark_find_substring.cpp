//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

//g++ -O3 benchmark_find_substring.cpp -o benchmark_find_substring.exe
//cl /Fo.\obj\ /EHsc /O2 benchmark_find_substring.cpp /link /out:benchmark_find_substring.exe

#include "helpers_and_types.hpp"

#define PICOBENCH_IMPLEMENT
#include "picobench.hpp"

int run_benchmark(int argc, char* argv[])
{
    picobench::runner runner;
    runner.parse_cmd_line(argc, argv);
    return runner.run();
}

#include <cstddef>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>

const std::size_t NOT_FOUND = -1;

std::size_t brute_force_substring(const std::string& text, const std::string& pattern)
{
    const std::size_t T = text.size();
    const std::size_t P = pattern.size();

    if (P <= T)
    {
        for (std::size_t i = 0; i <= T - P; ++i)
        {
            std::size_t j = 0;
            while (j < P)
            {
                if (text[i + j] != pattern[j])
                    break;
                ++j;
            }
            if (j == P)
                return i;
        }
    }
    return NOT_FOUND;
}

std::size_t kmp_substring(const std::string& text, const std::string& pattern)
{
    const std::size_t T = text.size();
    const std::size_t P = pattern.size();

    if (P <= T)
    {
        //build shift table
        std::vector<std::size_t> shift(P, -1);
        std::size_t j = -1;
        for (std::size_t i = 1; i < P; ++i)
        {
            while (j != -1 && pattern[j + 1] != pattern[i])
                j = shift[j];
            if (pattern[j + 1] == pattern[i])
                ++j;
            shift[i] = j;
        }
        //print shift table
        //for (std::size_t s : shift)
        //    std::cout << (int)s << " ";
        //std::cout << "\n";

        //find substring
        j = -1;
        for (std::size_t i = 0; i < T; ++i)
        {
            while (j != -1 && pattern[j + 1] != text[i])
                j = shift[j];
            if (pattern[j + 1] == text[i])
                ++j;
            if (j == P - 1)
                return i - (P - 1);
        }
    }
    return NOT_FOUND;
}

std::vector<std::size_t> kmp_table(const std::string& pattern)
{
    const std::size_t P = pattern.size();    
    std::vector<std::size_t> shift(P, -1);
    std::size_t j = -1;
    for (std::size_t i = 1; i < P; ++i)
    {
        while (j != -1 && pattern[j + 1] != pattern[i])
            j = shift[j];
        if (pattern[j + 1] == pattern[i])
            ++j;
        shift[i] = j;
    }    
    return shift;
}

std::size_t kmp_substring(const std::string& text, const std::string& pattern, const std::vector<std::size_t>& shift)
{
    const std::size_t T = text.size();
    const std::size_t P = pattern.size();

    if (P <= T)
    {
        std::size_t j = -1;
        for (std::size_t i = 0; i < T; ++i)
        {
            while (j != -1 && pattern[j + 1] != text[i])
                j = shift[j];
            if (pattern[j + 1] == text[i])
                ++j;
            if (j == P - 1)
                return i - (P - 1);
        }
    }
    return NOT_FOUND;
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

void bench_brute_force_string(picobench::state& s)
{
    const std::string& text = get_singleton_test_string();
    std::string pattern = text.substr(0, 3); pattern += '?'; //not found
    int n = s.iterations(), counter = 0;
    s.start_timer();
    while(n--)
    {
        if (NOT_FOUND != brute_force_substring(text, pattern))
            ++counter;
    }
    s.stop_timer();
    std::cout << s.iterations() << ' ' << pattern.substr(0, 15) << ' ' << counter << '\n';
}

struct adhoc_shift_table_tag {};
struct precomputing_shift_table_tag {};

void bench_kmp_string(picobench::state& s, adhoc_shift_table_tag)
{
    const std::string& text = get_singleton_test_string();
    std::string pattern = text.substr(0, 3); pattern += '?'; //not found
    int n = s.iterations(), counter = 0;
    s.start_timer();
    while(n--)
    {
        if (NOT_FOUND != kmp_substring(text, pattern))
            ++counter;
    }
    s.stop_timer();    
    std::cout << s.iterations() << ' ' << pattern.substr(0, 15) << ' ' << counter << '\n';
}

void bench_kmp_string(picobench::state& s, precomputing_shift_table_tag)
{
    const std::string& text = get_singleton_test_string();
    std::string pattern = text.substr(0, 3); pattern += '?'; //not found
    std::vector<std::size_t> shift = kmp_table(pattern);
    int n = s.iterations(), counter = 0;
    s.start_timer();
    while(n--)
    {
        if (NOT_FOUND != kmp_substring(text, pattern, shift))
            ++counter;
    }
    s.stop_timer();    
    std::cout << s.iterations() << ' ' << pattern.substr(0, 15) << ' ' << counter << '\n';
}

template <typename SHIFT_TABLE_TAG>
void bench_kmp_string(picobench::state& s)
{
     bench_kmp_string(s, SHIFT_TABLE_TAG{});
}

void bench_brute_force_dna(picobench::state& s)
{
    const std::vector<std::string>& data = get_singleton_test_string_vec();
    std::string pattern = "ACTGACAACAT"; //not found 
    //std::string pattern = "ACTGACAACA"; //found some
    //std::string pattern = "ACTGACAACAGCAACCTGTGTTA"; //found few
    int n = std::min<int>(s.iterations(), data.size()), m = (n >> 4), counter = 0;
    s.start_timer();
    while(m--)
    {
        for (int i = 0; i < n; ++i)
        {
            const std::string& text = data[i];
            if (NOT_FOUND != brute_force_substring(text, pattern))
                ++counter;
        }
    }
    s.stop_timer();
    std::cout << n << ' ' << pattern.substr(0, 15) << ' ' << counter << '\n';
}

void bench_kmp_dna(picobench::state& s, adhoc_shift_table_tag)
{
    const std::vector<std::string>& data = get_singleton_test_string_vec();
    std::string pattern = "ACTGACAACAT"; //not found
    //std::string pattern = "ACTGACAACA"; //found some
    //std::string pattern = "ACTGACAACAGCAACCTGTGTTA"; //found few
    int n = std::min<int>(s.iterations(), data.size()), m = (n >> 4), counter = 0;
    s.start_timer();
    while (m--)
    {
        for (int i = 0; i < n; ++i)
        {    
            const std::string& text = data[i];
            if (NOT_FOUND != kmp_substring(text, pattern))
                ++counter;
        }
    }
    s.stop_timer();
    std::cout << n << ' ' << pattern.substr(0, 15) << ' ' << counter << '\n';
}

void bench_kmp_dna(picobench::state& s, precomputing_shift_table_tag)
{
    const std::vector<std::string>& data = get_singleton_test_string_vec();
    std::string pattern = "ACTGACAACAT"; //not found
    //std::string pattern = "ACTGACAACA"; //found some
    //std::string pattern = "ACTGACAACAGCAACCTGTGTTA"; //found few
    std::vector<std::size_t> shift = kmp_table(pattern);
    int n = std::min<int>(s.iterations(), data.size()), m = (n >> 4), counter = 0;
    s.start_timer();
    while (m--)
    {
        for (int i = 0; i < n; ++i)
        {    
            const std::string& text = data[i];
            if (NOT_FOUND != kmp_substring(text, pattern, shift))
                ++counter;
        }
    }
    s.stop_timer();
    std::cout << n << ' ' << pattern.substr(0, 15) << ' ' << counter << '\n';
}

template <typename SHIFT_TABLE_TAG>
void bench_kmp_dna(picobench::state& s)
{
    bench_kmp_dna(s, SHIFT_TABLE_TAG{});
}

void register_benchmarks()
{
    /*
    std::vector<int> ITERS { 1 << 5, 1 << 6, 1 << 7, 1 << 8, 1 << 9, 1 << 10 };

    picobench::global_registry::set_bench_suite("substring_search string pattern");
    picobench::global_registry::new_benchmark("bench_brute_force_str", bench_brute_force_string).iterations(ITERS);
    picobench::global_registry::new_benchmark("bench_kmp_str_adhoc", bench_kmp_string<adhoc_shift_table_tag>).iterations(ITERS);
    picobench::global_registry::new_benchmark("bench_kmp_str_precomp", bench_kmp_string<precomputing_shift_table_tag>).iterations(ITERS);
    */
    
    std::vector<int> ITERS2 { 1 << 5, 1 << 6, 1 << 7, 1 << 8, 1 << 9, 1 << 10, 1 << 11, 1 << 12 };

    picobench::global_registry::set_bench_suite("substring_search dna pattern (adhoc shift table)");
    picobench::global_registry::new_benchmark("bench_brute_force_dna", bench_brute_force_dna).iterations(ITERS2);
    picobench::global_registry::new_benchmark("bench_kmp_dna", bench_kmp_dna<adhoc_shift_table_tag>).iterations(ITERS2);
    
    picobench::global_registry::set_bench_suite("substring_search dna pattern (precomputing shift table)");
    picobench::global_registry::new_benchmark("bench_brute_force_dna", bench_brute_force_dna).iterations(ITERS2);
    picobench::global_registry::new_benchmark("bench_kmp_dna", bench_kmp_dna<precomputing_shift_table_tag>).iterations(ITERS2);
}

int main(int argc, char* argv[])
{
    get_singleton_test_string();
    get_singleton_test_string_vec();
    register_benchmarks();
    return run_benchmark(argc, argv);
}