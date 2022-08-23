#include <cstddef>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <iomanip>

class Solution {
public:
    static void display_table(const std::vector<int>& bottles, const std::vector<std::size_t>& table, std::size_t rows, std::size_t cols)
    {
        const size_t INF = std::numeric_limits<std::size_t>::max();
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


    int coinC2hange(std::vector<int>& coins, int amount) 
    {
        const size_t INF = std::numeric_limits<std::size_t>::max();
        std::sort(coins.begin(), coins.end());

        std::size_t rows = coins.size();
        std::size_t cols = amount + 1;
        std::vector<std::size_t> table(rows * cols, 0);

        for(std::size_t row = 0; row < rows; ++row)
        {
            for(std::size_t col = 1; col < cols; ++col)
            {
                std::size_t up = row > 0 ? table[(row - 1) * cols + col] : INF;
                if(col < coins[row])
                    table[row * cols + col] = up;
                else
                {
                    std::size_t left = table[row * cols + (col - coins[row])];
                    table[row*cols + col] = std::min(up, left != INF ? 1 + left : INF);
                }
            }
        }

        std::cout << '\n';
        display_table(coins, table, rows, cols);
        std::size_t result = table[(rows - 1) * cols + (cols - 1)];
        if (result != INF)
            std::cout << result << " Bottle(s) needed\n";
        else
            std::cout << "Can't fill the recipient!\n";        

        return result;    
    }
};