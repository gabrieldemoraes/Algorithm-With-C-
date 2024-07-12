//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "cpf.hpp"
#include "helpers_and_types.hpp"

#include <vector>
#include <array>
#include <set>
#include <utility>
#include <algorithm>
#include <random>
#include <cstddef>
#include <cctype>
#include <iostream>
#include <iomanip>

#include "picobench.hpp"

namespace cpf
{
    static std::vector<cpf_type> generate_valid_cpfs(std::size_t n)
    {
        std::vector<cpf_type> cpfs;
        while (n--)
        {
            auto random_numbers = generate_random_ints(9, 0, 9);
            cpf_numbers_type numbers;
            std::transform(random_numbers.begin(), random_numbers.end(), numbers.begin(), [](int i){ return '0' + i; });
            cpfs.push_back(std::make_pair(numbers, cpf::v1::compute_digits(numbers)));
        }
        return cpfs;
    }

    static std::vector<cpf_type> generate_invalid_cpfs(std::size_t n)
    {
        std::vector<cpf_type> cpfs = generate_valid_cpfs(n);
        for (auto& cpf : cpfs)
        {
            int temp = cpf.second[0] - '0';
            cpf.second[0] = temp == 9 ? '0' : temp + 1 + '0';
        }
        return cpfs;
    }

    static std::vector<cpf_type> generate_random_cpfs(std::size_t n_valids, std::size_t n_invalids)
    {
        auto cpfs = generate_valid_cpfs(n_valids);
        for (auto cpf : generate_invalid_cpfs(n_invalids)) cpfs.push_back(cpf);
        shuffle(cpfs.begin(), cpfs.end());
        return cpfs;
    }

    static std::vector<cpf_type>& get_singleton_cpfs()
    {
        static std::vector<cpf_type> cpfs = generate_random_cpfs(800'000, 200'000);
        return cpfs;
    }
    
    static void bench_cpf_v1(picobench::state& s)
    {
        static std::vector<cpf_type> cpfs = get_singleton_cpfs();
        int n = s.iterations(), counter = 0;
        s.start_timer();
        while(n--)
        {
            auto& cpf = cpfs[n];
            counter += cpf::v1::is_valid(cpf);
        }
        s.stop_timer();
        std::cout << "cpfs valid counter v1: " << std::setw(7) << counter 
                  << " of " << std::setw(7) << s.iterations() << '\n';
    }

    static void bench_cpf_v2(picobench::state& s)
    {
        static std::vector<cpf_type> cpfs = get_singleton_cpfs();
        int n = s.iterations(), counter = 0;
        s.start_timer();
        while(n--)
        {
            auto& cpf = cpfs[n];
            counter += cpf::v2::is_valid(cpf);
        }        
        s.stop_timer();
        std::cout << "cpfs valid counter v2: " << std::setw(7) << counter 
                  << " of " << std::setw(7) << s.iterations() << '\n';
    }
    
    static void register_benchmarks()
    {
        std::vector<int> ITERS{ 10'000, 100'000, 250'000, 500'000, 1'000'000 };
        
        picobench::global_registry::set_bench_suite("cpfs validation");
        picobench::global_registry::new_benchmark("bench_cpf_v1", bench_cpf_v1).iterations(ITERS).baseline();
        picobench::global_registry::new_benchmark("bench_cpf_v2", bench_cpf_v2).iterations(ITERS);
    }

    static void test_interactive()
    {
        auto is_digit = [](char c) { return std::isdigit(static_cast<unsigned char>(c)); };

        std::cout << "string<9 digits>: generate cpf digits, ?<11 digits>: validate cpf, !: list tested cpfs, EOF: benchmark\n";

        std::set<std::string> cpfs;
        std::string cmd;
        while (std::cout << "> ", std::cin >> cmd)
        {
            switch (cmd[0])
            {
            case '!':
                {
                    std::cout << cpfs.size() << " cpf(s) already tested\n";
                    for (auto cpf : cpfs)
                        std::cout << cpf << ' ';
                    std::cout << '\n';
                }
                break;
            case '?':
                {
                    std::string s = cmd.substr(1);
                    if (s.size() == 11 && std::all_of(s.begin(), s.end(), is_digit))
                    {
                        cpf_type cpf;
                        std::copy(s.begin(), s.begin() + 9, cpf.first.begin());
                        std::copy(s.begin() + 9, s.end(), cpf.second.begin());
                        std::cout << "cpf is " << (cpf::v2::is_valid(cpf) ? "valid" : "invalid") << '\n';
                        cpfs.insert(to_string(cpf.first) + "-" + to_string(cpf.second));
                    }
                    else
                    {
                        std::cout << "input ignored\n";
                    }
                }
                break;
            default:
                {
                    if (cmd.size() == 9 && std::all_of(cmd.begin(), cmd.end(), is_digit))
                    {
                        cpf_numbers_type cpf_numbers;
                        std::copy(cmd.begin(), cmd.end(), cpf_numbers.begin());
                        cpf_digits_type cpf_digits = cpf::v2::compute_digits(cpf_numbers);
                        std::cout << to_string(cpf_digits) << '\n';
                        cpfs.insert(to_string(cpf_numbers) + "-" + to_string(cpf_digits));
                    }
                    else
                    {
                        std::cout << "input ignored\n";
                    }
                }
                break;
            }
        }
    }
}

int cpf_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using cpf::test_interactive;
    using cpf::register_benchmarks;

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