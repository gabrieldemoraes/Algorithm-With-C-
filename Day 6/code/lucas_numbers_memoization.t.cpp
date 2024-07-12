//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include <iostream>
#include <iomanip>
#include <map>

#include "picobench.hpp"

namespace lucas_numbers_memoization
{
    //recursive
    static long long lucas(short int n)
    {
        if (n == 0) return 2LL;
        if (n == 1) return 1LL;
        return lucas(n - 1) + lucas(n - 2);
    }

    //tail recursive
    static long long lucas_tailrec(short int n, long long current, long long next)
    {
        if (n == 0) return current;
        return lucas_tailrec(n - 1, next, current + next);
    }

    static long long lucas_tailrec(short int n)
    {
        return lucas_tailrec(n, 2LL, 1LL);
    }

    //dynamic programming: memoization
    class lucas_with_memoization
    {
        using map_type = std::map<short int, long long>;
        map_type memo;
    public:
        long long operator()(short int n)
        {
            if (n == 0) return 2LL;
            if (n == 1) return 1LL;
            map_type::iterator it = memo.find(n);
            if (it != memo.end())
                return it->second;
            long long result = (operator()(n - 1) + operator()(n - 2));
            memo.emplace(n, result);
            return result;
        }
    };

    static void bench_lucas(picobench::state& s)
    {
        short int n = s.iterations();

        s.start_timer();
        long long result = lucas(n);
        s.stop_timer();
                                          
        std::cout << std::setw(7) << n << "            bench_lucas: " << std::setw(12) << result << "\n";
    }

    static void bench_lucas_tailrec(picobench::state& s)
    {
        short int n = s.iterations();
        
        s.start_timer();
        long long result = lucas_tailrec(n);
        s.stop_timer();

        std::cout << std::setw(7) << n << "    bench_lucas_tailrec: " << std::setw(12) << result << "\n";
    }

    static lucas_with_memoization& get_singleton_lucas_memo()
    {
        static lucas_with_memoization lucas_memo;
        return lucas_memo;
    }

    static void bench_lucas_memo(picobench::state& s)
    {
        short int n = s.iterations();
        lucas_with_memoization& lucas_memo = get_singleton_lucas_memo();

        s.start_timer();
        long long result = lucas_memo(n);
        s.stop_timer();

        std::cout << std::setw(7) << n << "       bench_lucas_memo: " << std::setw(12) << result << "\n";
    }

    static void register_benchmarks()
    {
        std::vector<int> ITERS{ 5, 10, 15, 20 };
        std::vector<int> ITERS2{ 64, 128, 256, 512, 1024, 2048, 4096, 8192 };

        picobench::global_registry::set_bench_suite("lucas recursive: overlapping (naive) vs. memoization");
        picobench::global_registry::new_benchmark("bench_lucas", bench_lucas).iterations(ITERS);
        picobench::global_registry::new_benchmark("bench_lucas_memo", bench_lucas_memo).iterations(ITERS).baseline();

        picobench::global_registry::set_bench_suite("lucas recursive: overlapping (tail) vs. memoization");
        picobench::global_registry::new_benchmark("bench_lucas_tailrec", bench_lucas_tailrec).iterations(ITERS2);
        picobench::global_registry::new_benchmark("bench_lucas_memo", bench_lucas_memo).iterations(ITERS2);
    }

    static void run_solution()
    {
        //https://oeis.org/A000032
        //Lucas numbers beginning at 2: L(n) = L(n - 1) + L(n - 2), L(0) = 2, L(1) = 1.
        //2, 1, 3, 4, 7, 11, 18, 29, 47, 76, 123, 199, 322, 521, 843, 1364, 2207, 3571, 5778, 
        //9349, 15127, 24476, 39603, 64079, 103682, 167761, 271443, 439204, 710647, 1149851, 1860498, 
        //3010349, 4870847, 7881196, 12752043, 20633239, 33385282, 54018521, 87403803

        std::cout << "Lucas:\n";
        for (short int i = 0; i < 42; ++i)		
            std::cout << "L(" << i << ") = " << lucas(i) << "\n";		

        std::cout << "Lucas tail recursive:\n";
        for (short int i = 0; i < 42; ++i)			
            std::cout << "L(" << i << ") = " << lucas_tailrec(i) << "\n";
        
        std::cout << "Lucas with memoization:\n";
        lucas_with_memoization lucas_memo;
        for (short int i = 0; i < 42; ++i)
            std::cout << "L(" << i << ") = " << lucas_memo(i) << "\n";
    }
}

int lucas_numbers_memoization_main(int argc, char *argv[], bool run)
{
    using lucas_numbers_memoization::run_solution;
    using lucas_numbers_memoization::register_benchmarks;

    if (run)
    {
        run_solution();
        register_benchmarks();
    }

    return 0;
}