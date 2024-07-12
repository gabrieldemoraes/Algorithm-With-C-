//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 letter_combinations_of_a_phone_number.cpp -o letter_combinations_of_a_phone_number.exe
//cl /Fo.\obj\ /EHsc /O2 letter_combinations_of_a_phone_number.cpp /link /out:letter_combinations_of_a_phone_number.exe

#include <vector>
#include <string>
#include <algorithm>

const char* D[]
{
    "abc",  //2
    "def",  //3
    "ghi",  //4
    "jkl",  //5
    "mno",  //6
    "pqrs", //7
    "tuv",  //8
    "wxyz"  //9
};

void lc_rec(int i, const std::string& digits, std::string a, std::vector<std::string>& acc)
{
    if (i == digits.size())
    {
        acc.push_back(a);
        return;
    }

    const char* p = D[digits[i] - '2'];
    while (*p != '\0')
    {
        lc_rec(i + 1, digits, a + *p, acc);
        ++p;
    }
}

std::vector<std::string> letter_combinations_0(std::string digits)
{
    std::vector<std::string> acc;
    acc.reserve(256);
    lc_rec(0, digits, "", acc);
    return acc;
}

std::vector<std::string>& lc_recursive(int i, const std::string& digits, std::vector<std::string>& acc)
{
    if (i == digits.size())
        return acc;

    const size_t n = acc.size();
    for (size_t j = 0; j < n; ++j)	
        for (const char* p = D[digits[i] - '2']; *p != '\0'; ++p)
            acc.emplace_back(acc[j] + *p);
    acc.erase(acc.begin(), acc.begin() + n);
    
    return lc_recursive(i + 1, digits, acc);
}

std::vector<std::string>& lc_trampoline(const std::string& digits, std::vector<std::string>& acc)
{
    for (const char* p = D[digits[0] - '2']; *p != '\0'; ++p)
        acc.emplace_back(std::string(1, *p));
    return lc_recursive(1, digits, acc);
}

std::vector<std::string> letter_combinations_1(std::string digits)
{
    if (digits.size())
    {
        std::vector<std::string> acc;
        acc.reserve(256);
        return lc_trampoline(digits, acc);
    }
    return std::vector<std::string>();
}

std::vector<std::string> letter_combinations_2(std::string digits)
{
    std::vector<std::string> acc;
    if (digits.size() > 0)
    {
        for (const char* p = D[digits[0] - '2']; *p != '\0'; ++p)
            acc.emplace_back(std::string(1, *p));

        for (size_t i = 1, l = digits.size(); i < l; ++i)
        {
            const size_t n = acc.size();
            for (size_t j = 0; j < n; ++j)
                for (const char* p = D[digits[i] - '2']; *p != '\0'; ++p)
                    acc.emplace_back(acc[j] + *p);
            acc.erase(acc.begin(), acc.begin() + n);
        }
    }
    return acc;
}

#include <iterator>
#include <cstring>
#include <numeric>

std::vector<std::string> letter_combinations_3(std::string digits)
{
    std::vector<std::string> acc;
    if (digits.size() > 0)
    {
        const char* p = D[digits[0] - '2'];
        std::transform(p, p + std::strlen(p), std::back_inserter(acc), [](char ch) { return std::string(1, ch); });		
        acc = std::accumulate(digits.begin() + 1, digits.end(), acc,
            [&](const std::vector<std::string>& acc2, char digit) {
                return std::move(std::accumulate(acc2.begin(), acc2.end(), std::vector<std::string>(), [digit](std::vector<std::string>& acc3, const std::string& prefix) {
                    const char* p = D[digit - '2'];
                    std::transform(p, p + std::strlen(p), std::back_inserter(acc3), [prefix](char ch) {
                        return prefix + ch;
                    });
                    return std::move(acc3);
                }));
            });
    }
    return acc;
}

#include <iostream>

void display(const std::vector<std::string>& xs, const char* label)
{
    std::cout << label << ":\n";
    for (const std::string& x : xs)
        std::cout << x << ' ';
    std::cout << '\n' << std::endl;
}

//Test cases:
//23
//9
//9999
//45683
int main()
{
    std::string digits;
    std::cin >> digits;
    
    if (digits.end() == std::find_if_not(digits.begin(), digits.end(), [](char ch){ return '2' <= ch && ch <= '9'; }))
    {
        display(letter_combinations_0(digits), ("letter_combinations_0 " + digits).c_str());
        display(letter_combinations_1(digits), ("letter_combinations_1 " + digits).c_str());
        display(letter_combinations_2(digits), ("letter_combinations_2 " + digits).c_str());
        display(letter_combinations_3(digits), ("letter_combinations_3 " + digits).c_str());
    }

    return 0;
}