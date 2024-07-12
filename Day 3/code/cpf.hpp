//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org

#ifndef CPF_HPP
#define CPF_HPP

#include <array>
#include <string>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <utility>
#include <cstddef>
#include <cstdint>

namespace cpf
{
    using cpf_numbers_type = std::array<char, 9>;
    using cpf_digits_type  = std::array<char, 2>;
    using cpf_type         = std::pair<cpf_numbers_type, cpf_digits_type>;

    namespace internals
    {
        template <typename F>
        bool is_valid(cpf_type cpf, F compute_digits)
        {
            cpf_numbers_type numbers;
            cpf_digits_type digits;
            std::tie(numbers, digits) = cpf;
            cpf_digits_type temp = compute_digits(numbers);
            return temp[0] == digits[0] && temp[1] == digits[1];
        }
    };

    namespace v1
    {
        cpf_digits_type compute_digits(cpf_numbers_type numbers)
        {
            int fst = 0;
            int init = 10;
            for (char c : numbers)
                fst += ((c - '0') * init--);
            fst %= 11;
            fst = fst < 2 ? 0 : 11 - fst;
            
            int snd = 0;
            init = 11;
            for (char c : numbers)
                snd += ((c - '0') * init--);
            snd = (snd + (fst * init)) % 11;
            snd = snd < 2 ? 0 : 11 - snd;

            return { char('0' + fst), char('0' + snd) };
        }

        bool is_valid(cpf_type cpf)
        {
            return internals::is_valid(cpf, compute_digits);
        }
    }

    namespace v2
    {
        cpf_digits_type compute_digits(cpf_numbers_type numbers)
        {
            std::array<int, 9> A { 0 };
            std::array<int, 9> B { 10, 9, 8, 7, 6, 5, 4, 3, 2 };
            std::transform(numbers.begin(), numbers.end(), A.begin(), [](char c){ return c - '0'; });
            int A_dot = std::inner_product(A.begin(), A.end(), B.begin(), 0);
            int fst = A_dot % 11;
            fst = fst < 2 ? 0 : 11 - fst;
            int snd = ((A_dot + std::accumulate(A.begin(), A.end(), 0)) + fst * 2) % 11;
            snd = snd < 2 ? 0 : 11 - snd;
            return { char('0' + fst), char('0' + snd) };
        }

        bool is_valid(cpf_type cpf)
        {
            return internals::is_valid(cpf, compute_digits);
        }
    }
}

#endif /* CPF_HPP */