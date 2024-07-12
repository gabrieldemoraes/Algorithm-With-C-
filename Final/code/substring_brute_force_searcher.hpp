//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef SUBSTRING_BRUTE_FORCE_SEARCHER_HPP
#define SUBSTRING_BRUTE_FORCE_SEARCHER_HPP

#include "substring_searcher.hpp"

#include <cstddef>
#include <string>

namespace substring_searcher
{
    struct brute_force final : public substring_searcher<brute_force>
    {
        using base = substring_searcher<brute_force>;
        
        explicit brute_force(const std::string& pattern) 
            : base(pattern) {}

    private:
        friend base;

        std::size_t search_algo(const std::string& text, std::size_t init) const
        {
            const std::size_t T = text.size();
            const std::size_t P = pattern.size();
            if (P <= T + init)
            {
                for (std::size_t i = init; i <= T - P; ++i)
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
    };
}

#endif /* SUBSTRING_BRUTE_FORCE_SEARCHER_HPP */