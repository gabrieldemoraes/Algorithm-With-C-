//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef SUBSTRING_KMP_SEARCHER_HPP
#define SUBSTRING_KMP_SEARCHER_HPP

#include "substring_searcher.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace substring_searcher
{
    struct knuth_morris_pratt final : substring_searcher<knuth_morris_pratt>
    {
        using base = substring_searcher<knuth_morris_pratt>;

        explicit knuth_morris_pratt(const std::string& pattern)
            : base(pattern), shift(pattern.size(), -1)
        {
            const int P = static_cast<int>(pattern.size());
            int j = -1;
            for (int i = 1; i < P; ++i)
            {
                while (j >= 0 && pattern[j + 1] != pattern[i]) 
                    j = shift[j];
                if (pattern[j + 1] == pattern[i]) ++j;
                shift[i] = j;
            }
        }

    private:
        friend base;

        std::size_t search_algo(const std::string& text, std::size_t init) const
        {
            const std::size_t T = text.size();
            const std::size_t P = pattern.size() - 1;
            if ((P + 1) <= T + init)
            {
                std::size_t j = -1;
                for (std::size_t i = init; i < T; ++i)
                {
                    while (j != -1 && pattern[j + 1] != text[i])
                        j = shift[j];
                    if (pattern[j + 1] == text[i]) ++j;
                    if (j == P)
                        return i - P;
                }
            }
            return std::string::npos;
        }

    private:
        std::vector<int> shift;
    };
}

struct kmp_online
{
    explicit kmp_online(const std::string& pattern)
        : pattern(pattern), shift(pattern.size(), -1)
    {
        const int P = static_cast<int>(pattern.size());
        int j = -1;
        for (int i = 1; i < P; ++i)
        {
            while (j >= 0 && pattern[j + 1] != pattern[i]) 
                j = shift[j];
            if (pattern[j + 1] == pattern[i]) ++j;
            shift[i] = j;
        }
    }

    std::size_t search(char ch) const
    {
        const std::size_t P = pattern.size() - 1;
        while (j != -1 && pattern[j + 1] != ch)
            j = shift[j];
        if (pattern[j + 1] == ch) ++j;
        if (j == P)
        {
            j = shift[j];
            return (i++) - P;
        }   
        ++i;
        return std::string::npos;
    }

private:
    mutable std::size_t i = 0;
    mutable std::size_t j = -1;
    std::string pattern;
    std::vector<int> shift;
};

#endif /* SUBSTRING_KMP_SEARCHER_HPP */