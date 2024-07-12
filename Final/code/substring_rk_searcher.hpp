//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#ifndef SUBSTRING_RK_SEARCHER_HPP
#define SUBSTRING_RK_SEARCHER_HPP

#include "substring_searcher.hpp"

#include <cstddef>
#include <string>

#include <iostream>

namespace substring_searcher
{
    struct rabin_karp final : public substring_searcher<rabin_karp>
    {
        using base = substring_searcher<rabin_karp>;

        explicit rabin_karp(const std::string& pattern)
            : base(pattern), pattern_hash(hash(pattern, pattern.size())), 
              remove_factor(remove_hash(pattern.size())) {}

    private:
        friend base;

        static const std::size_t RADIX = 256 /* Extended ASCII */;
        static const std::size_t PRIME = 101;

        std::size_t search_algo(const std::string& text, std::size_t init) const
        {
            const std::size_t T = text.size();
            const std::size_t P = pattern.size();
            
            if (P <= T + init)
            {
                std::size_t text_hash = hash(text, P, init);

                if (pattern_hash == text_hash && substring_match(text, init))
                    return init;
                
                for (std::size_t i = init + 1; i <= T - P; ++i)
                {
                    //sliding window
                    char rem_char = text[i - 1], add_char = text[i - 1 + P];
                    text_hash = (text_hash + PRIME - remove_factor * rem_char % PRIME);
                    text_hash = (text_hash % PRIME * RADIX + add_char) % PRIME;
                    
                    if (pattern_hash == text_hash && substring_match(text, i))
                        return i;
                }
            }

            return std::string::npos;
        }

        bool substring_match(const std::string& text, std::size_t i) const
        {
            for (std::size_t j = 0; j < pattern.size(); ++j)
                if (text[i + j] != pattern[j])
                    return false;
            return true;
        }

        static std::size_t hash(const std::string& s, std::size_t size, std::size_t init = 0)
        {
            std::size_t h = s[init];
            for (std::size_t i = init + 1; i < (size + init); ++i)
                h = (RADIX * h + s[i]) % PRIME;
            return h;
        }

        static std::size_t remove_hash(std::size_t pattern_size)
        {
            std::size_t k = 1;
            for (std::size_t i = 1; i < pattern_size; ++i)
                k = (RADIX * k) % PRIME;
            return k;
        }

    private:
        std::size_t pattern_hash;
        std::size_t remove_factor;
    };
}

#endif /* SUBSTRING_RK_SEARCHER_HPP */