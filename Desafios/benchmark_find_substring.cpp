//g++ -O3 benchmark_find_substring.cpp -o benchmark_find_substring.exe

#include <iostream>
#include <string>
#define PICOBENCH_DEFAULT_ITERATIONS {1000, 10000, 100000, 1000000}
#define PICOBENCH_IMPLEMENT
#include "../Day 4/code/picobench.hpp"

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
    return std::string::npos;
}
        
std::size_t kmp_substring(const std::string& text, const std::string& pattern)
{
    std::vector<int> shift(pattern.size(), -1);
    const int P = static_cast<int>(pattern.size());
    int j = -1;
    for (int i = 1; i < P; ++i)
    {
        while (j >= 0 && pattern[j + 1] != pattern[i]) 
            j = shift[j];
        if (pattern[j + 1] == pattern[i]) ++j;
        shift[i] = j;
    }

    const std::size_t T = text.size();
    if ((P + 1) <= T)
    {
        std::size_t j = -1;
        for (std::size_t i = 0; i < T; ++i)
        {
            while (j != -1 && pattern[j + 1] != text[i])
                j = shift[j];
            if (pattern[j + 1] == text[i]) 
                ++j;
            if (j == pattern.size() - 1)
                return i - P;
        }
    }

    return NOT_FOUND;
}

static void bench_brute_force_substring(picobench::state& s)
{
    s.start_timer();
    size_t result;
    for (int i = 0; i < s.iterations(); ++i)
        result = brute_force_substring("ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBABABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBABABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBABABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBABABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAB", "ABC");
    s.stop_timer();		             
}


static void bench_kmp_substring(picobench::state& s)
{
    s.start_timer();
    size_t result;
    for (int i = 0; i < s.iterations(); ++i)
        result = kmp_substring("ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBABABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBABABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBABABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBABABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAB", "ABC");
    s.stop_timer();		     		             
}

static void register_benchmarks()
{
    picobench::global_registry::set_bench_suite("Benchmark_find_substring");
    picobench::global_registry::new_benchmark("brute_force_substring", bench_brute_force_substring);
    picobench::global_registry::new_benchmark("kmp_substring", bench_kmp_substring);
}

static int test_benchmarks(int argc, char *argv[])
{
    picobench::runner runner;
    runner.parse_cmd_line(argc, argv);
    return runner.run();
}

int find_substring_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    register_benchmarks();
    test_benchmarks(argc, argv);
    return 0;
}

int main(int argc, char *argv[])
{
    find_substring_main(argc, argv, true, true);	
    return 0;
}