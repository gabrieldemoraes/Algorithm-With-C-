//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include <cstddef>
#include <vector>
#include <cmath>
#include <iostream>

#include "picobench.hpp"

namespace enumerate_primes
{
    static std::vector<int> brute_force_primes(int n)
    {
        std::vector<int> primes;
        if (n >= 2)
        {
            for (int i = 2; i <= n; ++i)
            {
                bool is_prime = true;
                int m = static_cast<int>(std::floor(std::sqrt(i)));
                for (int j = 2; j <= m; ++j)
                {
                    is_prime = (i % j) != 0;
                    if (!is_prime)
                        break;
                }
                if (is_prime)
                    primes.push_back(i);
            }
        }
        return primes;
    }

    static std::vector<int> sieving_primes(int n)
    {
        std::vector<int> primes;
        if (n >= 2)
        {
            ++n;
            std::vector<bool> is_prime(n, true); is_prime[0] = is_prime[1] = false;
            for (int i = 2; i < n; ++i)
            {
                if (is_prime[i])
                    primes.push_back(i);
                for (int j = 2 * i; j < n; j += i) //sieve multiples of i
                    is_prime[j] = false;
            }
        }
        return primes;
    }

    static void bench_brute_force(picobench::state& s)
    {
        int n = s.iterations();
        s.start_timer();
        std::vector<int> primes = brute_force_primes(n);
        s.stop_timer();
        
        std::cout << n << ": ";
        std::size_t N = primes.size();
        if (N > 10)
            for (std::size_t i = N - 10; i < N; ++i) std::cout << primes[i] << " ";
        else
            for (int p : primes) std::cout << p << " ";
        std::cout << "\n";
    }

    static void bench_sieving(picobench::state& s)
    {
        int n = s.iterations();
        s.start_timer();
        std::vector<int> primes = sieving_primes(n);
        s.stop_timer();

        std::cout << n << ": ";
        std::size_t N = primes.size();
        if (N > 10)
            for (std::size_t i = N - 10; i < N; ++i) std::cout << primes[i] << " ";
        else
            for (int p : primes) std::cout << p << " ";
        std::cout << "\n";
    }

    static void register_benchmarks()
    {
        std::vector<int> ITERS{ 512, 1024, 2048, 4096, 8192, 16384, 32768 };
        
        picobench::global_registry::set_bench_suite("enumerate all primes to n using brute force");
        picobench::global_registry::new_benchmark("bench_brute_force", bench_brute_force).iterations(ITERS);

        picobench::global_registry::set_bench_suite("enumerate all primes to n using sieving");
        picobench::global_registry::new_benchmark("bench_sieving", bench_sieving).iterations(ITERS);
    }
}

int enumerate_primes_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using enumerate_primes::register_benchmarks;

    if (reg_benchmarks)
    {
        register_benchmarks();
    }

    return 0;
}