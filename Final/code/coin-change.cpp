//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 coin-change.cpp -o coin-change.exe
//cl /Fo.\obj\ /EHsc /O2  coin-change.cpp /link /out:coin-change.exe

#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>

int coin_change(const std::vector<int>& coins, int amount) 
{
    const int INF = static_cast<int>(std::numeric_limits<std::size_t>::max());
    const std::size_t rows = coins.size();
    const std::size_t cols = amount + 1;
    std::vector<int> table(rows * cols, 0);
    for (std::size_t row = 0; row < 1; ++row)
    {
        for (std::size_t col = 1; col < cols; ++col)
        {
            std::size_t  up = INF;
            if (col < coins[row])
            {
                table[row * cols + col] = up;
            }
            else
            {
                std::size_t left = table[row * cols + (col - coins[row])];
                table[row * cols + col] = std::min(up, left != INF ? 1 + left : INF);
            }
        }
    }
    for (std::size_t row = 1; row < rows; ++row)
    {
        for (std::size_t col = 1; col < cols; ++col)
        {
            std::size_t  up = table[(row - 1) * cols + col];
            if (col < coins[row])
            {
                table[row * cols + col] = up;
            }
            else
            {
                std::size_t left = table[row * cols + (col - coins[row])];
                table[row * cols + col] = std::min(up, left != INF ? 1 + left : INF);
            }
        }
    }
    return *std::prev(table.end());
}

#include <iostream>

//Test cases:
//3 1 2 5 11
//1 2 3
//1 1 0
//1 1 1
//1 1 2
int main()
{
    int N, amount;
    std::cin >> N;
    std::vector<int> coins(N, 0);
    for (std::size_t i = 0; i < N; ++i)
        std::cin >> coins[i];
    std::cin >> amount;

    int count = coin_change(coins, amount);    
    std::cout << "fewest number of coins that you need to make up that amount (" << amount << "): " << count << '\n';

    return 0;
}