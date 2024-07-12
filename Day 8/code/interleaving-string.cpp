//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 interleaving-string.cpp -o interleaving-string.exe
//cl /Fo.\obj\ /EHsc /O2 interleaving-string.cpp /link /out:interleaving-string.exe

#include <cstddef>
#include <string>
#include <vector>
#include <iterator>

bool is_string_interleave(std::string s1, std::string s2, std::string s3) 
{
    std::size_t rows = s1.size(), cols = s2.size();
    if (rows + cols != s3.size())
        return false;

    std::vector<bool> table((++rows) * (++cols));

    table[0] = true;

    for (std::size_t i = 0, l = rows - 1; i < l; ++i)
        table[(i + 1) * cols] = s1[i] == s3[i] ? table[i * cols]  : false;

    for (std::size_t j = 0, l = cols - 1; j < l; ++j)
        table[j + 1] = s2[j] == s3[j] ? table[j] : false;

    for (std::size_t i = 1; i < rows; ++i)
    {
        char c1 = s1[i - 1];
        for (std::size_t j = 1; j < cols; ++j)
        {
            char c2 = s2[j - 1];
            char c3 = s3[i + j - 1];
            bool ok_left = c2 == c3;
            bool   ok_up = c1 == c3;
            bool   up = table[(i - 1) * cols + j];
            bool left = table[i * cols + (j - 1)];
            table[i * cols + j] = (up && ok_up) || (left && ok_left);
        }
    }

    return *std::prev(table.end());
}

#include <iostream>
#include <iomanip>

void is_string_interleave_display(std::string s1, std::string s2, std::string s3)
{
    std::cout << '[' << s1 << "] and [" << s2 << "] is interleaving to [" << s3 << "]? "
        << std::boolalpha << is_string_interleave(s1, s2, s3) << '\n';
}

#include <algorithm>
#include <random>
#include <chrono>

int main()
{
    is_string_interleave_display("AB", "CD", "ABCD");

    is_string_interleave_display("AB", "AA", "AAAB");

    is_string_interleave_display("aabcc", "dbbca", "aadbbcbcac");

    is_string_interleave_display("aabcc", "dbbca", "aadbbbaccc");

    is_string_interleave_display("", "", "");

    is_string_interleave_display("db", "b", "cbb");

    is_string_interleave_display("HELLO", "WORLD", "HWEOLRLLOD");

    for (int i = 0; i < 10; ++i)
    {
        std::string s1 = "AB";
        std::string s2 = "BA";
        std::string s3 = s1 + s2;
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(s3.begin(), s3.end(), std::default_random_engine(seed));
        is_string_interleave_display(s1, s2, s3);
    }

    return 0;
}