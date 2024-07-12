//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include "helpers_and_types.hpp"

#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <cstddef>
#include <iomanip>

#include "picobench.hpp"

namespace stock_prices_max_profit
{
    static std::vector<int> get_singleton_opening_prices()
    {
        static std::vector<int> opening_prices = generate_random_ints(150000, 1, 1000);
        return opening_prices;
    }

    static void display_opening_prices()
    {
        for (int i : get_singleton_opening_prices())
            std::cout << i << " ";
        std::cout << "\n";
    }

    static int brute_force_sol(std::vector<int>& prices, int N)
    {
        int max_profit = 0;
        for (std::size_t i = 0; i < N - 1; ++i)
        {
            for (std::size_t j = i + 1; j < N; ++j)
            {
                if (prices[j] - prices[i] > max_profit)
                {
                    max_profit = prices[j] - prices[i];
                }
            }
        }
        return max_profit;
    }
    
    static void bench_brute_force_sol(picobench::state& s)
    {
        std::vector<int> prices = get_singleton_opening_prices();
        int N = std::min(s.iterations(), static_cast<int>(prices.size()));
        s.start_timer();
        int max_profit = brute_force_sol(prices, N);
        s.stop_timer();
        std::cout << std::setw(6) << N << "/" << std::setw(7) << s.iterations()
            << " brute  max profit: " << max_profit << "\n";
    }

    static int linear_sol(std::vector<int>& prices, int N)
    {
        int min_val = std::numeric_limits<int>::max();
        int max_profit = 0;
        for (std::size_t i = 0; i < N; ++i)
        {
            min_val = std::min(prices[i], min_val);
            max_profit = std::max(max_profit, prices[i] - min_val);
        }
        return max_profit;
    }

    static void bench_linear_sol(picobench::state& s)
    {
        std::vector<int> prices = get_singleton_opening_prices();
        int N = std::min(s.iterations(), static_cast<int>(prices.size()));
        s.start_timer();
        int max_profit = linear_sol(prices, N);
        s.stop_timer();
        std::cout << std::setw(6) << N << "/" << std::setw(7) << s.iterations()
            << " linear max profit: " << max_profit << "\n";
    }

    static void register_benchmarks()
    {
        picobench::global_registry::set_bench_suite("stock_prices_max_profit");
        picobench::global_registry::new_benchmark("bench_brute_force_sol", bench_brute_force_sol);
        picobench::global_registry::new_benchmark("bench_linear_sol", bench_linear_sol);
    }

    static void run_solution()
    {
        //PROBLEM: Given a sequence of stock's opening price. 
        //Compute the max profit (buying low, selling high)
        
        //INPUT: PRICES
        //Our input represents the sequence of stock's opening price from day 0 to day PRICES.size() - 1  
        //prices are normalized to int

        unsigned int opening_price_at_day;
        unsigned int min_val = std::numeric_limits<unsigned int>::max();
        unsigned int max_profit = 0;
        std::cout << "stock's opening price sequence [EOF to stop]:\n";
        while (std::cin >> opening_price_at_day)
        {
            //SOLUTION:
            min_val = std::min(opening_price_at_day, min_val);
            max_profit = std::max(max_profit, opening_price_at_day - min_val);
        }
        std::cout << "max profit: " << max_profit << "\n";
    }
}

//Test cases:
//Max profit is 6: 7 3 9 3 7 5 8 5 2 6
//Max profit is 15: 5 14 9 7 14 17 9 14 16 10 20 9 7 19 15
//Max profit is 7: 2 9 2 6 5 4 8 8
//Max profit is 117: 73 148 80 190 71 81 184 162 93 160 106 149
//Max profit is 118: 73 148 80 190 71 81 189 162 93 160 106 149
//Max profit is 137: 92 101 163 159 63 119 99 183 135 200 91 75
int stock_prices_max_profit_main(int argc, char *argv[], bool run_tests, bool reg_benchmarks)
{
    using stock_prices_max_profit::run_solution;
    using stock_prices_max_profit::register_benchmarks;

    if (reg_benchmarks)
    {
        register_benchmarks();
    }

    if (run_tests)
    {
        run_solution();
    }

    return 0;
}