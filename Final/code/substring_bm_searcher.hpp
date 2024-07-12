//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef SUBSTRING_BM_SEARCHER_HPP
#define SUBSTRING_BM_SEARCHER_HPP

#include "substring_searcher.hpp"

#include <cstddef>
#include <array>
#include <string>

namespace substring_searcher
{
    struct boyer_moore final : public substring_searcher<boyer_moore>
    {
        using base = substring_searcher<boyer_moore>;

        explicit boyer_moore(const std::string& pattern)
            : base(pattern), right{-1} 
        {
            const int P = static_cast<int>(pattern.size());
            for (int i = 0; i < P; ++i)
                right[pattern[i]] = i;
        }

    private:
        friend base;

        static const std::size_t RADIX = 256 /* Extended ASCII */;
        
        std::size_t search_algo(const std::string& text, std::size_t init) const
        {
            const int T = static_cast<int>(text.size());
            const int P = static_cast<int>(pattern.size());
            const int I = static_cast<int>(init);
            if (P <= T + I)
            {
                for (int i = I, step = 0; i <= T - P; i += step)
                {
                    step = 0;
                    for (int j = P - 1; j >= 0; --j)
                    {
                        if (text[i + j] != pattern[j])
                        {
                            step = j - right[text[i + j]];
                            if (step < 1) step = 1;
                            break;
                        }
                    }
                    if (step == 0)
                        return i;
                }
            }
            return std::string::npos;
        }

    private:
        std::array<int, RADIX> right;
    };
}

#endif /* SUBSTRING_RK_SEARCHER_HPP */