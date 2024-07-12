//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#include "binomial_coefficient.hpp"

#include <cstdint>
#include <iostream>

namespace binomial_coefficient
{
    static void test_interactive()
    {
        std::uint32_t n, k;
        while (std::cout << "n k: ", std::cin >> n >> k)
        {
            if (k <= n && 0 <= k && 0 <= n)
            {
                std::cout << "binomial coefficient(" << n << ',' << k << ") = ";
                std::cout << binomial_coefficient::binomial_coefficient_dp(n, k) << '\n';
            }
            else
            {
                std::cout << "invalid input\n";
            }
        }
    }
}

int binomial_coefficient_main(int argc, char *argv[], bool run_tests)
{
    using binomial_coefficient::test_interactive;
    
    //std::cout << binomial_coefficient::binomial_coefficient_recursive(5, 3) << '\n';
    //std::cout << binomial_coefficient::binomial_coefficient_dp(5, 3) << '*' << '\n';
    //std::cout << binomial_coefficient::binomial_coefficient_dp(8, 8) << '*' << '\n';

    if (run_tests)
    {
        test_interactive();
    }

    return 0;
}