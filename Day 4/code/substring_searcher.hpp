//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef SUBSTRING_SEARCHER_HPP
#define SUBSTRING_SEARCHER_HPP

#include <cstddef>
#include <string>

namespace substring_searcher
{
    template <typename T>
    struct substring_searcher
    {
        std::size_t search(const std::string& text, std::size_t init = 0) const
        {
            const T& derived = static_cast<const T&>(*this);
            return derived.search_algo(text, init);
        }

        substring_searcher() = delete;
        ~substring_searcher() = default;

    protected:
        explicit substring_searcher(const std::string& pattern)
            : pattern(pattern) {}

    protected:
        std::string pattern;
    };
}

#endif /* SUBSTRING_SEARCHER_HPP */