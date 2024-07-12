//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 cpf_algorithm.cpp -o cpf_algorithm.exe
//cl /Fo.\obj\ /EHsc /O2 cpf_algorithm.cpp /link /out:cpf_algorithm.exe

#include <array>
#include <algorithm>
#include <numeric>

using cpf_first_nine_digits_t = std::array<char, 9>;
using cpf_last_two_digits_t = std::array<char, 2>;

cpf_last_two_digits_t compute_cpf_last_two_digits_v1(cpf_first_nine_digits_t first_nine_digits)
{
    //reverse algorithm version:
    /*
    std::reverse(first_nine_digits.begin(), first_nine_digits.end());
    std::array<int, 9> a;
    std::transform(first_nine_digits.begin(), first_nine_digits.end(), a.begin(), [](char ch) { return ch - '0'; });
    */
    //reverse iterator version:
    std::array<int, 9> a;
    std::transform(first_nine_digits.rbegin(), first_nine_digits.rend(), a.begin(), [](char ch) { return ch - '0'; });
    int d1 = 0, d2 = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        d1 += a[i] * (9 - i);
        d2 += a[i] * (9 - i - 1);
    }
    d1 = d1 % 11 % 10;
    d2 = (d2 + d1 * 9) % 11 % 10;
    return cpf_last_two_digits_t { char('0' + d1), char('0' + d2) };
}

cpf_last_two_digits_t compute_cpf_last_two_digits_v1_improved(cpf_first_nine_digits_t first_nine_digits)
{
    std::array<int, 9> a;
    std::transform(first_nine_digits.rbegin(), first_nine_digits.rend(), a.begin(), [](char ch) { return ch - '0'; });
    int d1 = 0, d2 = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        int temp = a[i] * (9 - i);
        d1 += temp;
        d2 += temp;
    }
    for (int i = 0; i < a.size(); ++i)
    {
        d2 -= a[i];
    }
    d1 = d1 % 11 % 10;
    d2 = (d2 + d1 * 9) % 11 % 10;
    return cpf_last_two_digits_t { char('0' + d1), char('0' + d2) };
}

cpf_last_two_digits_t compute_cpf_last_two_digits_v2(cpf_first_nine_digits_t first_nine_digits)
{
    std::array<int, 9> a;
    std::array<int, 9> b{ 10, 9, 8, 7, 6, 5, 4, 3, 2 };
    std::transform(first_nine_digits.begin(), first_nine_digits.end(), a.begin(), [](char ch) { return ch - '0'; });
    int x = std::inner_product(a.begin(), a.end(), b.begin(), 0);
    int d1 = x % 11;
    d1 = d1 < 2 ? 0 : 11 - d1;
    int d2 = (2 * d1 + x + std::accumulate(a.begin(), a.end(), 0)) % 11;
    d2 = d2 < 2 ? 0 : 11 - d2;
    return cpf_last_two_digits_t { char('0' + d1), char('0' + d2) };
}

cpf_first_nine_digits_t to_first_nine_digits(const char* numbers)
{
    cpf_first_nine_digits_t first_nine_digits;
    std::copy(numbers, numbers + 9, first_nine_digits.begin());
    return first_nine_digits;
}

#include <iostream>

void display(cpf_last_two_digits_t digits)
{
    std::cout << digits[0] << digits[1] << "\n";
}

int main()
{
    display(compute_cpf_last_two_digits_v1(to_first_nine_digits("111444777")));
    display(compute_cpf_last_two_digits_v1_improved(to_first_nine_digits("111444777")));
    display(compute_cpf_last_two_digits_v2(to_first_nine_digits("111444777")));

    display(compute_cpf_last_two_digits_v1(to_first_nine_digits("123456789")));
    display(compute_cpf_last_two_digits_v1_improved(to_first_nine_digits("123456789")));
    display(compute_cpf_last_two_digits_v2(to_first_nine_digits("123456789")));
}