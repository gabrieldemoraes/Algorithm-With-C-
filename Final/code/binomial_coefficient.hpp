//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef BINOMIAL_COEFFICIENT_HPP
#define BINOMIAL_COEFFICIENT_HPP

#include <cstddef>
#include <cstdint>
#include <vector>
#include <algorithm>

namespace binomial_coefficient
{
    std::uint64_t binomial_coefficient_recursive(std::uint32_t n, std::uint32_t k)
    {
        //assert (k <= n && 0 <= k && 0 <= n)
        if (0 == k || k == n)
            return 1;
        return binomial_coefficient_recursive(n - 1, k - 1) + binomial_coefficient_recursive(n - 1, k);
    }

    std::uint64_t binomial_coefficient_dp(std::uint32_t n, std::uint32_t k)
    {
        //assert (k <= n && 0 <= k && 0 <= n)
        if (0 == k || k == n)
            return 1;
        if (k > (n >> 1)) k = n - k; //symmetry
        const std::uint32_t N = n + 1, K = k + 1;
        std::vector<std::uint64_t> B(N * K, -1);
        B[0] = 1;
        for (std::uint32_t i = 1; i < N; ++i)
        {
            B[i * K] = 1;
            for (std::uint32_t j = 1, l = std::min(k, i); j <= l; ++j)
                B[i * K + j] = B[(i - 1) * K + (j - 1)] +  B[(i - 1) * K + j];
            if (i < K)
                B[i * K + i] = 1;
        }
        return B[N * K - 1];
    }
}

#endif /* BINOMIAL_COEFFICIENT_HPP */