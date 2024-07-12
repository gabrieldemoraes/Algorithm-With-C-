//Source code do curso Algoritmos com C++ por Fabio Galuppo
//Ministrado em 2022 na Agit - https://www.agit.com.br/cursoalgoritmos.php
//Fabio Galuppo - http://member.acm.org/~fabiogaluppo - fabiogaluppo@acm.org
//This file is licensed to you under the MIT license

//g++ -O3 numeric_ops.cpp -o numeric_ops.exe
//cl /Fo.\obj\ /EHsc /O2 numeric_ops.cpp /link /out:numeric_ops.exe

#include <vector>
#include <set>
#include <string>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <iterator>

struct Combo
{
    std::vector<std::string> acc;    
};

inline static Combo& operator+(Combo& combo, std::string& s)
{
    std::size_t size = combo.acc.size();
    if (size > 0)
    {
        for (std::size_t i = 0; i < size; ++i)
        {
            for (char c : s)
                combo.acc.push_back(c + combo.acc[i]);
        }
        combo.acc.erase(combo.acc.begin(), combo.acc.begin() + size);
    }
    else
    {
        for (char c : s)
            combo.acc.push_back(std::string(1, c));
    }        
    return combo;
}

int main()
{
    std::vector<int> xs(10, 0);
    std::iota(xs.begin(), xs.end(), 1);

    std::cout << "Input: ";
    std::copy(xs.begin(), xs.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n\n";

    //accumulate

    int sumAll = std::accumulate(xs.begin(), xs.end(), 0);
    int sumFirstHalf = std::accumulate(xs.begin(), xs.begin() + xs.size() / 2, 0);
    int sumSecondHalf = std::accumulate(xs.begin() + xs.size() / 2, xs.end(), 0);    
    std::cout << sumAll << " " << sumFirstHalf << " " << sumSecondHalf << "\n";

    auto bin_mult = [](int acc, int x){ return acc * x; };
    int productAll = std::accumulate(xs.begin(), xs.end(), 1, bin_mult);
    int productFirstHalf = std::accumulate(xs.begin(), xs.begin() + xs.size() / 2, 1, bin_mult);
    int productSecondHalf = std::accumulate(xs.begin() + xs.size() / 2, xs.end(), 1, bin_mult);    
    std::cout << productAll << " " << productFirstHalf << " " << productSecondHalf << "\n";

    //partial_sum

    std::vector<int> ys(xs.size(), 0);
    std::partial_sum(xs.begin(), xs.end(), ys.begin());
    std::copy(ys.begin(), ys.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    //adjacent_difference

    std::vector<int> zs(xs.size(), 0);
    std::adjacent_difference(xs.begin(), xs.end(), zs.begin());
    std::copy(zs.begin(), zs.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    //inner_product
    
    int inner_prod = std::inner_product(xs.begin(), xs.end(), ys.begin(), 100);
    std::cout << inner_prod << "\n";
    
    std::cout << "\n" << std::string(20, '-') << "\n\n";

    //combination with accumulate

    std::vector<std::string> chs { "12", "34", "56", "78", "09" };
    std::cout << "Input: ";
    std::copy(chs.begin(), chs.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << "\n\n";
    
    /*
    std::vector<std::string> combo = std::accumulate(chs.begin(), chs.end(), std::vector<std::string>(), [](std::vector<std::string>& acc, const std::string& s) {
        std::size_t size = acc.size();
        if (size > 0)
        {
            for (std::size_t i = 0; i < size; ++i)
            {
                for (char c : s)
                    acc.push_back(c + acc[i]);
            }
            acc.erase(acc.begin(), acc.begin() + size);
        }
        else
        {
            for (char c : s)
                acc.push_back(std::string(1, c));
        }        
        return acc;
    });
   */
   std::vector<std::string> combo = std::accumulate(chs.begin(), chs.end(), Combo()).acc;
    
    std::transform(combo.begin(), combo.end(), combo.begin(), [](std::string& s) { 
        std::reverse(s.begin(), s.end());
        return std::move(s); 
    });
    std::copy(combo.begin(), combo.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << "\n";
    
    return 0;
}