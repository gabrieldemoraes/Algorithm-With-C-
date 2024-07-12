//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

#include <cstddef>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <iomanip>

namespace water_recipient_filling
{
    const size_t INF = std::numeric_limits<std::size_t>::max();

    static void display_table(const std::vector<std::size_t>& bottles, const std::vector<std::size_t>& table, std::size_t rows, std::size_t cols)
    {
        std::cout << std::setw(7) << ' ';
        for (std::size_t col = 0; col < cols; ++col)
            std::cout << std::setw(4) << col << ' ';
        std::cout << '\n';
        std::cout << "=======";
        for (std::size_t col = 0; col < cols; ++col)
            std::cout << "=====";
        std::cout << '\n';

        for (std::size_t row = 0; row < rows; ++row)
        {
            std::cout << std::setw(4) << bottles[row] << " | ";
            for (std::size_t col = 0; col < cols; ++col)
            {
                std::size_t b = table[row * cols + col];
                if (b == INF)
                    std::cout << std::setw(5) << "INF";
                else
                    std::cout << std::setw(4) << b << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
   
    static void water_recipient_filling(std::size_t recipient_capacity, std::vector<std::size_t> bottles)
    {
        std::sort(bottles.begin(), bottles.end());
        
        std::size_t rows = bottles.size();
        std::size_t cols = recipient_capacity + 1;
        std::vector<std::size_t> table(rows * cols, 0);
        for (std::size_t row = 0; row < rows; ++row)
        {
            for (std::size_t col = 1; col < cols; ++col)
            {
                std::size_t up = row > 0 ? table[(row - 1) * cols + col] : INF;
                if (col < bottles[row])
                {
                    table[row * cols + col] = up;
                }
                else
                {
                    std::size_t left = table[row * cols + (col - bottles[row])];
                    table[row * cols + col] = std::min(up, left != INF ? 1 + left : INF);
                }
            }
        }
        
        std::cout << '\n';
        display_table(bottles, table, rows, cols);
        std::size_t result = table[(rows - 1) * cols + (cols - 1)];
        if (result != INF)
            std::cout << result << " Bottle(s) needed\n";
        else
            std::cout << "Can't fill the recipient!\n";
    }
    
    static int run_solution()
    {
        //PROBLEM: Given the water recipient capacity and the bottles' capacity available.
        //Find the minimal number of bottles necessary to fill this recipient.

        //INPUT: W, N, capacities
        //Our input represents W (water recipient capacity), N (number of bottles) and capacities (sequence of bottle's capacity)

        std::size_t W, N;
        std::cin >> W >> N;
        std::vector<std::size_t> capacities(N, 0);
        for (std::size_t i = 0; i < N; ++i)
            std::cin >> capacities[i];
        
        //REQUIREMENTS:
        if (!std::all_of(capacities.begin(), capacities.end(), [W](std::size_t c) { return c <= W; }))
        {
            std::cout << "Invalid due an bottle greater than recipient capacity\n";
            return -1;
        }

        //SOLUTION:
        water_recipient_filling(W, std::move(capacities));

        return 0;
    }
}

//Test cases:
//1 Bottle(s) needed:  3 3 1 2 3
//2 Bottle(s) needed:  7 3 1 2 5
//3 Bottle(s) needed: 12 3 1 4 5
//3 Bottle(s) needed: 11 3 1 2 5
//3 Bottle(s) needed: 10 3 2 1 7
//4 Bottle(s) needed: 18 5 1 2 3 5 7
//5 Bottle(s) needed: 10 2 2 7
//Can't fill the recipient!: 9 1 2
int water_recipient_filling_main(int argc, char *argv[], bool run)
{
    using water_recipient_filling::run_solution;
    
    if (run)
    {
        return run_solution();
    }

    return 0;
}